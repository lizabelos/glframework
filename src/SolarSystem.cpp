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

    mBasicProgram = std::unique_ptr<GLTools::Program>(new GLTools::Program("res/shaders/basic3d.vs.glsl", "res/shaders/sun.fs.glsl"));
    mBegin = std::chrono::steady_clock::now();

}

void SolarSystem::render() {

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    float currentTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(end - mBegin).count() * 1e-6f;

    mBasicProgram->use();

    mCamera.identity();
    mCamera.scale(99.0f);
    mCamera.rotate(currentTime / 10, glm::vec3(0.0f, 1.0f, 0.0f));
    std::shared_ptr<GLTools::Texture> startexture = getTexture("Stars");
    startexture->activate(GL_TEXTURE0);
    mBasicProgram->post("uTexture", 0);
    mBasicProgram->post(mCamera);
    mSphere.render(mCamera);

    mCamera.identity();
    mCamera.translate(glm::vec3(0.0f, 0.0f, -20.0f));
    mCamera.rotate(currentTime / 10, glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera.rotate(3.14 / 2, glm::vec3(1.0f, 0.0f, 0.0f));


    for (const std::shared_ptr<Astronomy::Astre> &astre : mSystem->getAll()) {

        std::shared_ptr<GLTools::Texture> texture = getTexture(astre->getName());
        texture->activate(GL_TEXTURE0);
        mBasicProgram->post("uTexture", 0);

        mCamera.pushMatrix();

        glm::vec3 position = translationScale(astre->getPosition(currentTime));
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

std::shared_ptr<GLTools::Texture> SolarSystem::getTexture(const std::string &name) {
    if (mTextures.count(name) == 0) {
        mTextures[name] = std::shared_ptr<GLTools::Texture>(new GLTools::Texture("res/textures/" + name + ".jpg"));
    }
    return mTextures[name];
}
