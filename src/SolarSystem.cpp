//
// Created by thomas on 13/11/18.
//

#include "SolarSystem.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <memory>


SolarSystem::SolarSystem() : GLTools::Window("Solar System"), mSphere(256, 256) {

    std::ifstream solarfile("res/solarsystem.txt");
    if (!solarfile.is_open())
    {
        throw std::runtime_error("Can't open solarsystem.txt");
    }

    std::string line;
    bool firstIteration = true;

    while (getline(solarfile,line))
    {
        std::istringstream iss(line);
        std::vector<std::string> splits(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        std::string type = splits[0];
        std::string name = splits[1];
        float radius = static_cast<float>(atof(splits[2].c_str()));
        float rotationspeed = static_cast<float>(atof(splits[3].c_str()));

        if (firstIteration) {
            if (type != "Star") throw std::runtime_error("First entry must be a Star !");
            mSystem = std::make_unique<Astronomy::System>(std::make_shared<Astronomy::Star>(name, radius, rotationspeed));
            firstIteration = false;
            continue;
        }

        if (type == "Star") {
            // todo
            // std::shared_ptr<Astronomy::Astre> star = std::make_shared<Astronomy::Astre>(new Astronomy::Star(name, radius, rotationspeed));
            // mSystem->add(star);
        }

        if (type == "Planet") {
            // todo
        }

        std::cerr << "Warning : unkown type, '" + type + "'. Passing" << std::endl;



    }
    solarfile.close();

    if (firstIteration) {
        throw std::runtime_error("solarsystem.txt need at least one entry !");
    }

    mCamera.translate(glm::vec3(-10, 0, 0));

    mBasicProgram = std::unique_ptr<GLTools::Program>(new GLTools::Program("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl"));


}

void SolarSystem::render() {

    time_t currentTime;
    time(&currentTime);

    for (const std::shared_ptr<Astronomy::Astre> &astre : mSystem->getAll()) {

        mCamera.pushMatrix();

        mCamera.scale(radiusScale(astre->getRadius()));
        mCamera.rotate(astre->getRotation(currentTime));
        mCamera.translate(translationScale(astre->getPosition(currentTime)));

        mBasicProgram->use();
        mBasicProgram->post(mCamera);

        mSphere.render(mCamera);

        mCamera.popMatrix();

    }

}

glm::vec3 SolarSystem::translationScale(glm::vec3 translation) {
    return translation / 100.0f;
}

float SolarSystem::radiusScale(float radius) {
    return radius / 10.0f;
}

void SolarSystem::add(std::shared_ptr<Astronomy::Astre> astre) {
    // todo
}
