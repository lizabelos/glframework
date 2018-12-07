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


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(255, 256, 256), mSquare(1), mMouseRotation(false), mProportionalView(true), selectionHover(0), mFreefly(false), mPlay(true) {

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

    mRender2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/button2d.fs.glsl");
    mSelection2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");

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
    if (renderStep == GLTools::RENDER_SCREEN) mSphere.render(camera, program, renderStep);

    camera.identity();

    renderSystem(renderStep, camera, program, mStarSystem->getSystem(), 1);
}

void SolarSystem::render2d(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program) {

    program->use();
    mCamera2D.identity();
    mCamera2D.scale(0.1);


    mCamera2D.translate(glm::vec2(-0.7,-0.7));
    program->post(mCamera2D);
    program->post("uId", RENDERCODE_BUTTON_PROPVIEW);
    if (selectionHover == RENDERCODE_BUTTON_PROPVIEW) program->post("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else program->post("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mTextureProp->activate(GL_TEXTURE0);
    program->postTexture("uTexture", 0);
    mSquare.render(mCamera2D, program, renderStep);

    mCamera2D.translate(glm::vec2(0.3,0.0));
    program->post(mCamera2D);
    program->post("uId", RENDERCODE_BUTTON_CAMERAMODE);
    if (selectionHover == RENDERCODE_BUTTON_CAMERAMODE) program->post("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else program->post("uColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    mTextureCamera->activate(GL_TEXTURE0);
    program->postTexture("uTexture", 0);
    mSquare.render(mCamera2D, program, renderStep);

    mCamera2D.translate(glm::vec2(0.3,0.0));
    program->post(mCamera2D);
    program->post("uId", RENDERCODE_BUTTON_PLAY);
    if (selectionHover == RENDERCODE_BUTTON_PLAY) program->post("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else program->post("uColor", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    mTexturePlay->activate(GL_TEXTURE0);
    program->postTexture("uTexture", 0);
    mSquare.render(mCamera2D, program, renderStep);

}

void SolarSystem::renderSystem(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::System> system, int recursivity) {
    float currentTime = getTime() / 1000.0f;
    if (!mPlay) currentTime = lastTime;

    std::vector<std::shared_ptr<Astronomy::Astre>> astres = system->getAstres();
    std::sort(astres.begin(), astres.end(), [](const std::shared_ptr<Astronomy::Astre> &a, const std::shared_ptr<Astronomy::Astre> &b) { return a->getCenterDistance() < b->getCenterDistance(); });

    int i = 0;
    for (const std::shared_ptr<Astronomy::Astre> &astre : astres) {
        std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
        texture->activate(GL_TEXTURE0);
        program->postTexture("uTexture", 0);

        camera.pushMatrix();

        camera.translate(translationScale(astre->getPosition(currentTime), i));
        camera.scale(radiusScale(astre->getDiameter()));


        program->post(camera);
        program->post("uId", 255 - i);

        mSphere.render(camera, program, renderStep);


        if (astre->hasSystem()) {
            renderSystem(renderStep, camera, program, astre->getSystem(), recursivity + 1);
        }

        camera.popMatrix();



        i++;
    }

}


glm::vec3 SolarSystem::translationScale(glm::vec3 translation, int i) {
    //translation = glm::log(translation);
    // todo : need to normalize thanks to the center point of the astre
    float currentDistance = glm::distance(translation, glm::vec3(0, 0, 0));
    // float wantedDistance = (float)(i * 3) + currentDistance * 0.000000001f;
    float wantedDistance;
    if (mProportionalView) wantedDistance = (float)(i * 3) + sqrtf(currentDistance) / 1000.0f;
    else wantedDistance = i * 6;
    return translation / currentDistance * wantedDistance;
}

float SolarSystem::radiusScale(float radius) {
    if (!mProportionalView) return 1;
    radius = (1.0f + sqrtf(radius)) / 100.0f;
    return radius;
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
        mMouseRotation = false;
    }
}

void SolarSystem::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    glm::vec2 diff = mousePosition - mMouseStart;
    mMouseStart = mousePosition;
    if (!mFreefly) {
        if (mMouseRotation) {
        mTrackballCamera.rotateLeft(diff.x);
        mTrackballCamera.rotateUp(diff.y);
        }
    } else {
        mFreeflyCamera.rotateLeft(diff.x);
        mFreeflyCamera.rotateUp(diff.y);
    }
    

    selectionHover = selection;

}

void SolarSystem::keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key) {
    if (mFreefly) {
        switch (key.sym) {
            case SDLK_UP:
                mFreeflyCamera.moveFront(1.0f);
                break;
            case SDLK_LEFT:
                mFreeflyCamera.moveLeft(1.0f);
                break;
            case SDLK_RIGHT:
                mFreeflyCamera.moveLeft(-1.0f);
                break;
            case SDLK_DOWN:
                mFreeflyCamera.moveFront(-1.0f);
                break;
            default:
                break;
        }
    }
}
