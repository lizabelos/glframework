#include <memory>

#include <memory>

//
// Created by thomas on 13/11/18.
//

#include "SolarSystem.h"
#include "utility/CSVReader.h"
#include "astronomy/Description.h"
#include "astronomy/Parser.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <memory>
#include <algorithm>


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mPlanetDayTexture("res/planet_day"), mPlanetNightTexture("res/planet_night"), mRingColorTexture("res/ring_color"), mRingAlphaTexture("res/ring_alpha"), mSphere(255, 256, 256), mCircle3D(1, 256, true), mRing3D(1, 256, false, 0.75f), mSquare(1), mCube(1), mMouseRotation(false), mScaleType(Astronomy::PathScaleType::INDEX), selectionHover(0), mFreefly(false) {

    Astronomy::Parser::readCSV("res/system.csv", mStarSystem, mAstres);

    mTextureProp = std::make_shared<GLTools::Texture>("res/prop.png");
    mTexturePlay = std::make_shared<GLTools::Texture>("res/play.png");
    mTextureCamera = std::make_shared<GLTools::Texture>("res/camera.png");

    mBackground = std::make_shared<GLTools::TextureCubeMap>("res/background/lf.jpg", "res/background/dn.jpg", "res/background/up.jpg", "res/background/dn.jpg", "res/background/ft.jpg", "res/background/bk.jpg");

    mRender3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mSelection3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/selection3d.fs.glsl");
    mLine3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/white3d.fs.glsl");
    mLightProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/light.fs.glsl");
    mLightNightProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/lightnight.fs.glsl");
    mRingProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/ring.fs.glsl");

    mRender2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/button2d.fs.glsl");
    mSelection2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");

    mBackgroundProgram = std::make_shared<GLTools::Program>("res/shaders/cubmap.vs.glsl", "res/shaders/cubmap.fs.glsl");

    mCurrentSystem = mStarSystem;
}

void SolarSystem::render(GLTools::RenderStep renderStep) {


    if (!mFreefly) {
        render3d(renderStep, mTrackballCamera);
    } else {
        render3d(renderStep, mFreeflyCamera);
    }  

    render2d(renderStep);



}

void SolarSystem::render3d(GLTools::RenderStep renderStep, GLTools::Camera3D &camera)
{
    glDepthMask(GL_FALSE);
    camera.identity();
    camera.scale(500.0f);
    camera.disableTranslation();

    mBackground->activate(GL_TEXTURE0);
    mBackgroundProgram->use();
    mBackgroundProgram->post("uCubemap", 0);
    mBackgroundProgram->post(camera);

    if (renderStep == GLTools::RENDER_SCREEN) {
        mCube.render(camera, mBackgroundProgram, renderStep);
    }

    glDepthMask(GL_TRUE);
    camera.enableTranslation();

    camera.identity();

    int i = 1, subi = 0, mousei = 1;
    renderAstre(renderStep, camera, mCurrentSystem, i, subi, mousei);
}

void SolarSystem::render2d(GLTools::RenderStep renderStep) {

    mCamera2D.identity();

    renderButton(renderStep, RENDERCODE_BUTTON_PROPVIEW, glm::vec2(0, 0), mTextureProp, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    renderButton(renderStep, RENDERCODE_BUTTON_CAMERAMODE, glm::vec2(1, 0), mTextureCamera, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    renderButton(renderStep, RENDERCODE_BUTTON_PLAY, glm::vec2(2, 0), mTexturePlay, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));



}

void SolarSystem::renderButton(GLTools::RenderStep renderStep, int uId, glm::vec2 position, std::shared_ptr<GLTools::Texture> texture, glm::vec4 color, glm::vec4 hover) {

    std::shared_ptr<GLTools::Program> program;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            program = mRender2DProgram;
            break;
        case GLTools::RENDER_SELECTION:
            program = mSelection2DProgram;
            break;
    }
    program->use();

    mCamera2D.pushMatrix();
    mCamera2D.scale(0.1);
    mCamera2D.translate(position * 2.2f - glm::vec2(0.5f / 0.1f, 0.5f / 0.1f));
    program->post(mCamera2D);
    program->post("uId", uId);
    if (selectionHover == uId) program->post("uColor", hover);
    else program->post("uColor", color);
    texture->activate(GL_TEXTURE0);
    program->postTexture("uTexture", 0);
    mSquare.render(mCamera2D, program, renderStep);
    mCamera2D.popMatrix();

}

void SolarSystem::renderSystem(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<Astronomy::System> system, int &i, int &subi, int &mousei) {

    std::vector<std::shared_ptr<Astronomy::Astre>> astres = system->getAstres();
    std::sort(astres.begin(), astres.end(), [](const std::shared_ptr<Astronomy::Astre> &a, const std::shared_ptr<Astronomy::Astre> &b) { return a->getCenterDistance().y < b->getCenterDistance().y; });


    int ni = 1; subi++;
    for (const std::shared_ptr<Astronomy::Astre> &astre : astres) {
        renderAstre(renderStep, camera, astre, ni, subi, mousei);
    }
    subi--;

}

void SolarSystem::renderAstre(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<Astronomy::Astre> astre, int &i, int &subi, int &mousei) {


    float currentTime = mTimeManager.getTime() / 1000.0f;

    std::shared_ptr<GLTools::Program> program;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            if (astre->getDescription().nightLight) {
                program = mLightNightProgram;
                program->post("uDiffuseMin", 0.0f);
                mPlanetNightTexture[astre->getName()]->activate(GL_TEXTURE1);
                program->postTexture("uNightTexture", 1);

            } else {
                program = mLightProgram;

                if (subi == 0) {
                    program->post("uDiffuseMin", 1.0f);
                } else {
                    program->post("uDiffuseMin", 0.1f);
                }
            }

            if (astre->getDescription().texture) {
                mPlanetDayTexture[astre->getName()]->activate(GL_TEXTURE0);
                program->postTexture("uTexture", 0);
            } else {
                mPlanetDayTexture["Default"]->activate(GL_TEXTURE0);
                program->postTexture("uTexture", 0);
            }
            program->post("uLightPosition", camera.getViewMatrix() * glm::vec4(0,0,0,1));
            break;
        case GLTools::RENDER_SELECTION:
            program = mSelection3DProgram;
            break;
    }

    program->use();


    Astronomy::PathScale pathScale;

    pathScale.type = mScaleType;
    pathScale.param->set((float)i / (float)subi);
    pathScale.param2->set(1.0f / powf(10, subi - 1));

    if (mScaleType == Astronomy::PathScaleType::INDEX) {
        pathScale.param->set((float)i * 6.0f / powf(10, subi - 1));
    }


    if (renderStep == GLTools::RENDER_SCREEN && subi != 0) {
        camera.pushMatrix();

        Astronomy::AnglePath path = astre->getAnglePath(pathScale);

        GLGeometry::ParametricDrawable3D ellipse(0);

        Maths::SVariable p2 = Maths::make_SVariable();

        ellipse.initialize(path.x, path.y, path.z, path.x, path.y, path.z, path.x, path.y, path.angle, p2, 256, 1);
        ellipse.setLine(true);

        if (mScaleType != Astronomy::PathScaleType::INDEX) camera.rotate(
                    static_cast<float>(astre->getDescription().orbitalInclination / 180.0 * M_PI), glm::vec3(1.0f, 0.0f, 1.0f));

        ellipse.render(camera, mLine3DProgram, renderStep);
        camera.popMatrix();
    }

    camera.pushMatrix();


    Astronomy::TimePath path = astre->getTimePath(pathScale);
    path.time->set(currentTime);

    glm::vec3 translation = glm::vec3(path.x->get(), path.y->get(), path.z->get());


    if (mScaleType != Astronomy::PathScaleType::INDEX) {
        camera.rotate(static_cast<float>(astre->getDescription().orbitalInclination / 180.0 * M_PI), glm::vec3(1.0f, 0.0f, 1.0f));
    }

    if (subi != 0) {
        camera.translate(glm::vec3(path.x->get(), path.y->get(), path.z->get()));
    }

    camera.pushMatrix();
    camera.scale(path.radius->get());
    camera.rotate(path.rotation->get(), glm::vec3(0.0f, 1.0f, 0.0f));

    program->post(camera);
    program->post("uId", 255 - mousei);

    mSphere.render(camera, program, renderStep);
    i++;
    mousei++;

    if (renderStep == GLTools::RENDER_SCREEN && astre->getDescription().ringSystem) {
        camera.scale(1.0f);

        mRingAlphaTexture[astre->getName()]->activate(GL_TEXTURE0);
        mRingProgram->postTexture("uRingAlplha", 0);

        mRingColorTexture[astre->getName()]->activate(GL_TEXTURE1);
        mRingProgram->postTexture("uRingColor", 1);

        mRingProgram->post("uDiffuseMin", 0.1f);

        mRing3D.render(camera, mRingProgram, renderStep);
    }

    camera.popMatrix();
    if (astre->hasSystem()) {
        renderSystem(renderStep, camera, astre->getSystem(), i, subi, mousei);
    }
    camera.popMatrix();


}

std::shared_ptr<Astronomy::Astre> SolarSystem::searchAstre(std::shared_ptr<Astronomy::Astre> astre, int index, int &i) {

    if (index == i) return astre;

    i++;
    if (astre->hasSystem()) {
        for (const std::shared_ptr<Astronomy::Astre> &sastre : astre->getSystem()->getAstres()) {
            std::shared_ptr<Astronomy::Astre> result = searchAstre(sastre, index, i);
            if (result != nullptr) return result;
        }
    }

    return nullptr;

}

void SolarSystem::resize(unsigned int width, unsigned int height) {
    mTrackballCamera.resize(width, height);
    mFreeflyCamera.resize(width, height);
    mCamera2D.resize(width, height);
}

void SolarSystem::scroll(int x, int y) {
    if (!mFreefly) {
        if (y > 0) {
            mTrackballCamera.moveFront(1.0f / (y * 1.1f));
        }
        if (y < 0) {
            mTrackballCamera.moveFront((-y * 1.1f));
        }
    }
}

void SolarSystem::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {
    if (selection == 0 && state == SDL_PRESSED) {
        mMouseRotation = true;
        mMouseStart = mousePosition;
    }

    if (selection == RENDERCODE_BUTTON_PROPVIEW && state == SDL_RELEASED) {
        if (mScaleType == Astronomy::PathScaleType::INDEX) {
            mScaleType = Astronomy::PathScaleType::NORMAL;
        } else {
            mScaleType = (Astronomy::PathScaleType)(mScaleType + 1);
        }
    }

    if (selection == RENDERCODE_BUTTON_CAMERAMODE && state == SDL_RELEASED) {
        mFreefly = !mFreefly;
    }

    if (selection == RENDERCODE_BUTTON_PLAY && state == SDL_RELEASED) {
        mTimeManager.pauseplay();
    }

    if (state == SDL_RELEASED) {
        if (mMouseRotation) {
            mMouseRotation = false;
        }
    }

    if (state == SDL_PRESSED) {
        int planetid = 255 - selection; int i = 1;
        std::cout << "Click on planet : " << planetid << std::endl;
        std::shared_ptr<Astronomy::Astre> astre = searchAstre(mCurrentSystem, planetid, i);
        if (astre != nullptr) mCurrentSystem = astre;
        std::cout << "New system center : " << mCurrentSystem->getName() << std::endl;
    }
}

void SolarSystem::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    glm::vec2 diff = mousePosition - mMouseStart;
    mMouseStart = mousePosition;
    if (!mFreefly) {
        if (mMouseRotation) {
        mTrackballCamera.rotateLeft(diff.x * M_PI * 2);
        mTrackballCamera.rotateUp(diff.y * M_PI * 2);
        }
    } else {
        mFreeflyCamera.rotateLeft(diff.x * M_PI * 2);
        mFreeflyCamera.rotateUp(diff.y * M_PI * 2);
    }
    

    selectionHover = selection;


    int planetid = 255 - selection; int i = 1;
    std::shared_ptr<Astronomy::Astre> astre = searchAstre(mCurrentSystem, planetid, i);
    if (astre != nullptr) std::cout << "Mouse on planet : " << planetid << " " << astre->getName() << std::endl;

}

void SolarSystem::keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key) {
    if (mFreefly) {
        switch (key.sym) {
            case SDLK_UP:
            case SDLK_z:
                mFreeflyCamera.moveFront(1.0f);
                break;
            case SDLK_LEFT:
            case SDLK_q:
                mFreeflyCamera.moveLeft(1.0f);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                mFreeflyCamera.moveLeft(-1.0f);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                mFreeflyCamera.moveFront(-1.0f);
                break;
            case SDLK_LSHIFT:
                mFreeflyCamera.moveUp(1.0f);
                break;
            case SDLK_SPACE:
                mFreeflyCamera.moveUp(-1.0f);
                break;
            default:
                break;
        }
    }
    switch (key.sym) {
        case SDLK_c:
            if (type == SDL_KEYUP) mFreefly = !mFreefly;
            break;
        case SDLK_ESCAPE:
            mCurrentSystem = mStarSystem;
            std::cout << "New system center : " << mCurrentSystem->getName() << std::endl;
            break;
        case SDLK_o:
            mTimeManager.speedup();
            break;
        case SDLK_p:
            mTimeManager.seepdown();
            break;
        default:
            break;
    }
}