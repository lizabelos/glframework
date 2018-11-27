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


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(1, 256, 256), mZoom(1.0f), rotationX(0.0f), rotationY(0.0f), mouseRotation(false) {

    std::vector<std::vector<std::string>> csv = CSVReader::read("res/system.csv");

    std::map<std::string, int> entryMap;
    for (int i = 1; i < csv.size(); i++) {
        std::cout << "Property found " << csv[i][0] << std::endl;
        entryMap[csv[i][0]] = i;
    }

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

        description.diameter = atof(csv[entryMap["Diameter"]][i].c_str());
        description.rotationPeriod = atof(csv[entryMap["Rotation Period"]][i].c_str());
        description.sunDistance = atof(csv[entryMap["Distance from Sun"]][i].c_str()) * 10e6;
        description.orbitalPeriod = atof(csv[entryMap["Orbital Period"]][i].c_str());
        description.orbitalVelocity = atof(csv[entryMap["Orbital Velocity"]][i].c_str());
        description.orbitalInclination = atof(csv[entryMap["Orbital Inclination"]][i].c_str());
        description.moonNumber = atoi(csv[entryMap["Number of Moons"]][i].c_str());
        description.ringSystem = csv[entryMap["Ring System"]][i] == "Yes";

        if (i == 2) {
            std::shared_ptr<Astronomy::Star> star = std::make_shared<Astronomy::Star>(name, description);
            mSystem = std::make_unique<Astronomy::System>(star);

        } else {
            std::shared_ptr<Astronomy::Astre> planet = std::make_shared<Astronomy::Planet>(mSystem->getStar(), name, description);
            mSystem->add(planet);
        }

    }



    mBasicProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mSelectionProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/selection3d.fs.glsl");

}

void SolarSystem::render(GLTools::RenderStep renderStep) {

    std::shared_ptr<GLTools::Program> currentProgram;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            currentProgram = mBasicProgram;
            break;
        case GLTools::RENDER_SELECTION:
            currentProgram = mSelectionProgram;
            break;
    }

    float currentTime = getTime() / 1000;
    glm::vec2 mousePosition = getMousePosition();

    if (mouseRotation) {
        glm::vec2 diff = mousePosition - mMouseStart;
        mMouseStart = mousePosition;
        rotationX += diff.x;
        rotationY += diff.y;
    }


    currentProgram->use();

    mCamera.identity();
    mCamera.scale(1000.0f);
    mCamera.rotate(rotationX * 3.14f * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 xRotation =  glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), (float)(rotationX * 3.14), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera.rotate(rotationY * 3.14f * 2.0f, xRotation);
    std::shared_ptr<GLTools::Texture> startexture = getTexture("Stars");
    startexture->activate(GL_TEXTURE0);
    currentProgram->post("uTexture", 0);
    currentProgram->post(mCamera);
    if (renderStep == GLTools::RENDER_SCREEN) mSphere.render(mCamera, renderStep);

    mCamera.identity();
    mCamera.translate(glm::vec3(0.0f, 0.0f, -50.0f));
    mCamera.rotate(rotationX * 3.14f * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera.rotate(rotationY * 3.14f * 2.0f, xRotation);
    mCamera.scale(mZoom);


    int i = 0;

    std::vector<std::shared_ptr<Astronomy::Astre>> astres = mSystem->getAll();

    std::sort(astres.begin(), astres.end(),
            [](const std::shared_ptr<Astronomy::Astre> &a, const std::shared_ptr<Astronomy::Astre> &b) { return a->getCenterDistance() < b->getCenterDistance(); });

    for (const std::shared_ptr<Astronomy::Astre> &astre : astres) {

        std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
        texture->activate(GL_TEXTURE0);
        currentProgram->postTexture("uTexture", 0);

        mCamera.pushMatrix();

        mCamera.translate(translationScale(astre->getPosition(currentTime), i));
        mCamera.scale(radiusScale(astre->getDiameter()));

        currentProgram->post(mCamera);

        currentProgram->post("uId", i);

        mSphere.render(mCamera, renderStep);

        mCamera.popMatrix();

        i++;

    }

}

glm::vec3 SolarSystem::translationScale(glm::vec3 translation, int i) {
    //translation = glm::log(translation);
    // todo : need to normalize thanks to the center point of the astre
    float currentDistance = glm::distance(translation, glm::vec3(0, 0, 0));
    // float wantedDistance = (float)(i * 3) + currentDistance * 0.000000001f;
    float wantedDistance = (float)(i * 3) + sqrtf(currentDistance) / 1000.0f;
    return translation / currentDistance * wantedDistance;
}

float SolarSystem::radiusScale(float radius) {
    radius = (1.0f + sqrtf(radius)) / 100.0f;
    return radius;
}

std::shared_ptr<GLTools::Texture> SolarSystem::getTexture(const std::string &name) {
    if (mTextures.count(name) == 0) {
        mTextures[name] = std::shared_ptr<GLTools::Texture>(new GLTools::Texture("res/textures/" + name + ".jpg"));
    }
    return mTextures[name];
}

void SolarSystem::resize(unsigned int width, unsigned int height) {
    mCamera.resize(width, height);
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
        mouseRotation = true;
        mMouseStart = mousePosition;
    }

    if (state == SDL_RELEASED) {
        mouseRotation = false;
    }
}
