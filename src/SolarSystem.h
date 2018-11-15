//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include <list>
#include <chrono>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "gltools/Sphere"
#include "gltools/Program"
#include "astronomy/System"
#include "astronomy/Planet"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void render() override;

    glm::vec3 translationScale(glm::vec3 translation);
    float radiusScale(float radius);

private:
    GLTools::Camera mCamera;
    GLTools::Sphere mSphere;
    std::unique_ptr<Astronomy::System> mSystem;
    std::unique_ptr<GLTools::Program> mBasicProgram;

    std::chrono::steady_clock::time_point mBegin;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
