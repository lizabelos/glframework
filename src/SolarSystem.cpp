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
        std::vector<std::string> args(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        if (firstIteration) {
            if (args[0] != "Star") throw std::runtime_error("First entry must be a Star !");
            std::cout << "Parsing main star " << args[1] << "." << std::endl;
            mSystem = std::make_unique<Astronomy::System>(std::make_shared<Astronomy::Star>(args[1], atof(args[2].c_str()), atof(args[3].c_str())));
            firstIteration = false;
        }

        else if (args[0] == "Star") {
            std::cout << "Parsing star " << args[1] << "." << std::endl;
            mSystem->add(std::shared_ptr<Astronomy::Astre>(new Astronomy::Star(args[1], atof(args[2].c_str()), atof(args[3].c_str()))));
        }

        else if (args[0] == "Planet") {
            std::cout << "Parsing planet " << args[1] << "." << std::endl;
            mSystem->add(std::shared_ptr<Astronomy::Astre>(new Astronomy::Planet(mSystem->getStar(), args[1], atof(args[2].c_str()), atof(args[3].c_str()), atof(args[4].c_str()), atof(args[5].c_str()))));
        }

        else std::cerr << "Warning : unkown type, '" + args[0] + "'. Passing" << std::endl;



    }
    solarfile.close();

    if (firstIteration) {
        throw std::runtime_error("solarsystem.txt need at least one entry !");
    }

    mBasicProgram = std::unique_ptr<GLTools::Program>(new GLTools::Program("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl"));
    mBegin = std::chrono::steady_clock::now();

}

void SolarSystem::render() {


    mBasicProgram->use();

    mCamera.identity();
    mCamera.translate(glm::vec3(0.0f, 0.0f, -5.0f));

    //mBasicProgram->post(mCamera);
    // mSphere.render(mCamera);




    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();


    float currentTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(end - mBegin).count() * 1e-6f;

    for (const std::shared_ptr<Astronomy::Astre> &astre : mSystem->getAll()) {

        mCamera.pushMatrix();

        // mCamera.scale(radiusScale(astre->getRadius()));
        // mCamera.rotate(astre->getRotation(currentTime));
        glm::vec3 position = translationScale(astre->getPosition(currentTime));
        std::cout << astre->getName() << std::endl;
        std::cout << position.x << " " << position.y << " " << position.z << std::endl;
        mCamera.translate(position);

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
