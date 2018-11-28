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


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(255, 256, 256), mTriangle(1), mZoom(1.0f), mRotationX(0.0f), mRotationY(0.0f), mMouseRotation(false), mProportionalView(true) {

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



    mRender3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mSelection3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/selection3d.fs.glsl");

    mRender2DProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
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

    mCamera3D.identity();
    mCamera3D.scale(1000.0f);
    mCamera3D.rotate(mRotationX * 3.14f * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 xRotation =  glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), (float)(mRotationX * 3.14), glm::vec3(0.0f, 1.0f, 0.0f)));
    mCamera3D.rotate(mRotationY * 3.14f * 2.0f, xRotation);
    std::shared_ptr<GLTools::Texture> startexture = getTexture("Stars");
    startexture->activate(GL_TEXTURE0);
    program3D->post("uTexture", 0);
    program3D->post(mCamera3D);
    if (renderStep == GLTools::RENDER_SCREEN) mSphere.render(mCamera3D, program3D, renderStep);

    mCamera3D.identity();
    mCamera3D.translate(glm::vec3(0.0f, 0.0f, -50.0f));
    mCamera3D.rotate(mRotationX * 3.14f * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera3D.rotate(mRotationY * 3.14f * 2.0f, xRotation);
    mCamera3D.scale(mZoom);

    renderSystem(renderStep, program3D, mStarSystem->getSystem(), 1);

    program2D->use();
    mCamera2D.identity();
    mCamera2D.translate(glm::vec2(-0.7,-0.7));
    mCamera2D.scale(0.1);
    program2D->post(mCamera2D);
    program2D->post("uId", mTriangle.getCode());
    mTriangle.render(mCamera2D, program2D, renderStep);


}

void SolarSystem::renderSystem(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::System> system, int recursivity) {
    float currentTime = getTime() / 1000;

    std::vector<std::shared_ptr<Astronomy::Astre>> astres = system->getAstres();
    std::sort(astres.begin(), astres.end(), [](const std::shared_ptr<Astronomy::Astre> &a, const std::shared_ptr<Astronomy::Astre> &b) { return a->getCenterDistance() < b->getCenterDistance(); });

    int i = 0;
    for (const std::shared_ptr<Astronomy::Astre> &astre : astres) {
        std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
        texture->activate(GL_TEXTURE0);
        program->postTexture("uTexture", 0);

        mCamera3D.pushMatrix();

        mCamera3D.translate(translationScale(astre->getPosition(currentTime), i));
        mCamera3D.scale(radiusScale(astre->getDiameter()));


        program->post(mCamera3D);
        program->post("uId", 255 - i);

        mSphere.render(mCamera3D, program, renderStep);


        if (astre->hasSystem()) {
            renderSystem(renderStep, program, astre->getSystem(), recursivity + 1);
        }

        mCamera3D.popMatrix();



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
    mCamera3D.resize(width, height);
    mCamera2D.resize(width, height);
}

void SolarSystem::scroll(int x, int y) {
    if (y > 0) {
        mZoom = mZoom * (y * 1.1f);
    }
    if (y < 0) {
        mZoom = mZoom / (-y * 1.1f);
    }
}

void SolarSystem::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {
    if (selection == 0 && state == SDL_PRESSED) {
        mMouseRotation = true;
        mMouseStart = mousePosition;
    }

    if (selection == mTriangle.getCode() && state == SDL_PRESSED) {
        mProportionalView = !mProportionalView;
    }

    if (state == SDL_RELEASED) {
        mMouseRotation = false;
    }
}

void SolarSystem::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    if (mMouseRotation) {
        glm::vec2 diff = mousePosition - mMouseStart;
        mMouseStart = mousePosition;
        mRotationX += diff.x;
        mRotationY += diff.y;
    }

}

