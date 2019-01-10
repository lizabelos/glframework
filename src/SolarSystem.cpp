#include <memory>

#include <memory>

//
// Created by thomas on 13/11/18.
//

#include "SolarSystem.h"
#include "utility/CSVReader.h"
#include "astronomy/Description.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <memory>
#include <algorithm>


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(255, 256, 256), mCircle3D(1, 256, true), mRing3D(1, 256, false, 0.75f), mSquare(1), mMouseRotation(false), mProportionalView(true), selectionHover(0), mFreefly(false), mPlay(true) {

    std::vector<std::vector<std::string>> csv = CSVReader::read("res/system.csv");

    std::map<std::string, int> entryMap;
    for (int i = 1; i < csv.size(); i++) {
        std::cout << "Property found " << csv[i][0] << std::endl;
        entryMap[csv[i][0]] = i;
    }

    if (entryMap.count("Parent") != 1) throw std::runtime_error("Columns Parent not found");
    if (entryMap.count("Diameter") != 1) throw std::runtime_error("Columns Diameter not found");
    if (entryMap.count("Rotation Period") != 1) throw std::runtime_error("Columns Rotation Period not found");
    if (entryMap.count("Distance from Sun") != 1) throw std::runtime_error("Columns Distance from Sun not found");
    if (entryMap.count("Orbital Period") != 1) throw std::runtime_error("Columns Orbital Period not found");
    if (entryMap.count("Orbital Velocity") != 1) throw std::runtime_error("Columns Orbital Velocity not found");
    if (entryMap.count("Orbital Inclination") != 1) throw std::runtime_error("Columns Orbital Inclination not found");
    if (entryMap.count("Orbital Eccentricity") != 1) throw std::runtime_error("Columns Orbital Inclination not found");
    if (entryMap.count("Number of Moons") != 1) throw std::runtime_error("Columns Number of Moons not found");
    if (entryMap.count("Ring System") != 1) throw std::runtime_error("Columns Ring System not found");

    for (int i = 2; i < csv[0].size(); i++) {

        Astronomy::description_t description;

        std::string name = csv[0][i];
        std::cout << "Parsing " << name << std::endl;

        std::string parent = csv[entryMap["Parent"]][i];

        description.diameter = atof(csv[entryMap["Diameter"]][i].c_str());
        description.rotationPeriod = atof(csv[entryMap["Rotation Period"]][i].c_str());
        description.sunDistance = atof(csv[entryMap["Distance from Sun"]][i].c_str()) * 10e6;
        description.orbitalPeriod = atof(csv[entryMap["Orbital Period"]][i].c_str());
        description.orbitalVelocity = atof(csv[entryMap["Orbital Velocity"]][i].c_str());
        description.orbitalInclination = atof(csv[entryMap["Orbital Inclination"]][i].c_str());
        description.orbitalEccentricity = atof(csv[entryMap["Orbital Eccentricity"]][i].c_str());
        description.moonNumber = atoi(csv[entryMap["Number of Moons"]][i].c_str());
        description.ringSystem = csv[entryMap["Ring System"]][i] == "Yes";

        if (i == 2) {
            mStarSystem = std::make_shared<Astronomy::Star>(name, description);
            mAstres[name] = mStarSystem;
        } else {
            std::shared_ptr<Astronomy::Astre> planet = std::make_shared<Astronomy::Planet>(name, description);
            mAstres[parent]->getSystem()->add(planet);
            mAstres[name] = planet;
        }

    }

    mTextureProp = std::make_shared<GLTools::Texture>("res/prop.png");
    mTexturePlay = std::make_shared<GLTools::Texture>("res/play.png");
    mTextureCamera = std::make_shared<GLTools::Texture>("res/camera.png");



    mRender3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mSelection3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/selection3d.fs.glsl");
    mLine3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/white3d.fs.glsl");

    mRender2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/button2d.fs.glsl");
    mSelection2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");


    mCurrentSystem = mStarSystem;
}

void SolarSystem::render(GLTools::RenderStep renderStep) {

    std::shared_ptr<GLTools::Program> program3D, program2D;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            program3D = mRender3DProgram;
            program2D = mRender2DProgram;
            break;
        case GLTools::RENDER_SELECTION:
            program3D = mSelection3DProgram;
            program2D = mSelection2DProgram;
            break;
    }

    program3D->use();


    if (!mFreefly) {
        render3d(renderStep, mTrackballCamera, program3D);
    } else {
        render3d(renderStep, mFreeflyCamera, program3D);
    }  

    render2d(renderStep, program2D);




    if (mPlay) lastTime = getTime() / 1000.0f;
}

void SolarSystem::render3d(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<GLTools::Program> program)
{
    camera.identity();
    camera.scale(1000.0f);
    std::shared_ptr<GLTools::Texture> startexture = getTexture("Stars");
    startexture->activate(GL_TEXTURE0);
    program->post("uTexture", 0);
    program->post(camera);
    //if (renderStep == GLTools::RENDER_SCREEN) mSphere.render(camera, program, renderStep);

    camera.identity();

    int i = 1, subi = 0, mousei = 1;
    renderAstre(renderStep, camera, program, mCurrentSystem,
                i, subi, mousei);
}

void SolarSystem::render2d(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program) {

    program->use();
    mCamera2D.identity();

    renderButton(renderStep, program, RENDERCODE_BUTTON_PROPVIEW, glm::vec2(0, 0), mTextureProp, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    renderButton(renderStep, program, RENDERCODE_BUTTON_CAMERAMODE, glm::vec2(1, 0), mTextureCamera, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    renderButton(renderStep, program, RENDERCODE_BUTTON_PLAY, glm::vec2(2, 0), mTexturePlay, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));



}

void SolarSystem::renderButton(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program, int uId, glm::vec2 position, std::shared_ptr<GLTools::Texture> texture, glm::vec4 color, glm::vec4 hover) {

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

void SolarSystem::renderSystem(GLTools::RenderStep renderStep, GLTools::Camera3D &camera,
                               std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::System> system,
                               int &i, int &subi, int &mousei) {

    std::vector<std::shared_ptr<Astronomy::Astre>> astres = system->getAstres();
    std::sort(astres.begin(), astres.end(), [](const std::shared_ptr<Astronomy::Astre> &a, const std::shared_ptr<Astronomy::Astre> &b) { return a->getCenterDistance().y < b->getCenterDistance().y; });


    int ni = 1; subi++;
    for (const std::shared_ptr<Astronomy::Astre> &astre : astres) {
        renderAstre(renderStep, camera, program, astre,
                    ni, subi, mousei);
    }
    subi--;

}

void SolarSystem::renderAstre(GLTools::RenderStep renderStep, GLTools::Camera3D &camera,
                              std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::Astre> astre,
                              int &i, int &subi, int &mousei) {
    float currentTime = getTime() / 1000.0f;
    if (!mPlay) currentTime = lastTime;

    std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
    texture->activate(GL_TEXTURE0);
    program->postTexture("uTexture", 0);


    Astronomy::PathScale pathScale;

    if (mProportionalView) {
        pathScale.type = Astronomy::PathScaleType::LOGMUL;
        pathScale.param->set((float)i / (float)subi);
    } else {
        pathScale.type = Astronomy::PathScaleType::INDEX;
        pathScale.param->set((float)i * 6.0f / (float)subi);
    }


    if (renderStep == GLTools::RENDER_SCREEN && subi != 0) {
        camera.pushMatrix();

        Astronomy::AnglePath path = astre->getAnglePath(pathScale);

        GLGeometry::ParametricDrawable3D ellipse(0);

        Maths::SVariable p2 = Maths::make_SVariable();

        ellipse.initialize(path.x, path.y, path.z, path.x, path.y, path.z, path.x, path.y, path.angle, p2, 256, 1);
        ellipse.setLine(true);

        if (mProportionalView) camera.rotate(
                    static_cast<float>(astre->getDescription().orbitalInclination / 180.0 * M_PI), glm::vec3(1.0f, 0.0f, 1.0f));

        ellipse.render(camera, mLine3DProgram, renderStep);
        camera.popMatrix();
    }

    camera.pushMatrix();


    Astronomy::TimePath path = astre->getTimePath(pathScale);
    path.time->set(currentTime);

    glm::vec3 translation = glm::vec3(path.x->get(), path.y->get(), path.z->get());


    if (mProportionalView) {
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
        mRing3D.render(camera, mLine3DProgram, renderStep);
    }

    camera.popMatrix();
    if (astre->hasSystem()) {
        renderSystem(renderStep, camera, program, astre->getSystem(), i, subi, mousei);
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

std::shared_ptr<GLTools::Texture> SolarSystem::getTexture(const std::string &name) {
    if (mTextures.count(name) == 0) {
        mTextures[name] = std::make_shared<GLTools::Texture>("res/textures/" + name + ".jpg");
    }
    return mTextures[name];
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
        mProportionalView = !mProportionalView;
    }

    if (selection == RENDERCODE_BUTTON_CAMERAMODE && state == SDL_RELEASED) {
        mFreefly = !mFreefly;
    }

    if (selection == RENDERCODE_BUTTON_PLAY && state == SDL_RELEASED) {
        mPlay = !mPlay;
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
        default:
            break;
    }
}