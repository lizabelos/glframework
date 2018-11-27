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


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(256, 256) {

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



    mBasicProgram = std::unique_ptr<GLTools::Program>(new GLTools::Program("res/shaders/basic3d.vs.glsl", "res/shaders/sun.fs.glsl"));


}

void SolarSystem::render() {

    float currentTime = getTime() / 1000;
    glm::vec2 mousePosition = getMousePosition() - glm::vec2(0.5, 0.5);

    mBasicProgram->use();

    mCamera.identity();
    mCamera.scale(1000.0f);
    mCamera.rotate(mousePosition.x * 3.14, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 xRotation =  glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), (float)(mousePosition.x * 3.14), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera.rotate(mousePosition.y * 3.14, xRotation);
    std::shared_ptr<GLTools::Texture> startexture = getTexture("Stars");
    startexture->activate(GL_TEXTURE0);
    mBasicProgram->post("uTexture", 0);
    mBasicProgram->post(mCamera);
   // mSphere.render(mCamera);

    mCamera.identity();
    mCamera.translate(glm::vec3(0.0f, 0.0f, -50.0f));
    mCamera.rotate(mousePosition.x * 3.14, glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera.rotate(mousePosition.y * 3.14, xRotation);


    for (const std::shared_ptr<Astronomy::Astre> &astre : mSystem->getAll()) {

        std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
        texture->activate(GL_TEXTURE0);
        mBasicProgram->post("uTexture", 0);

        mCamera.pushMatrix();

        mCamera.translate(translationScale(astre->getPosition(currentTime)));
        mCamera.scale(radiusScale(astre->getDiameter()));

        mBasicProgram->post(mCamera);

        mSphere.render(mCamera);

        mCamera.popMatrix();

    }

}

glm::vec3 SolarSystem::translationScale(glm::vec3 translation) {
    //translation = glm::log(translation);
    std::cout << translation.x << " " << translation.y << " " << translation.z << std::endl;
    return translation;
}

float SolarSystem::radiusScale(float radius) {
    radius = glm::sqrt(glm::sqrt(radius)) * 10e-2f;
    std::cout << radius << std::endl;
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
