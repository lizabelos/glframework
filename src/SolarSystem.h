//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include <list>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "gltools/Sphere"
#include "gltools/Program"
#include "gltools/Texture"
#include "astronomy/System"
#include "astronomy/Planet"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void resize(unsigned int width, unsigned int height);
    void render() override;

    glm::vec3 translationScale(glm::vec3 translation);
    float radiusScale(float radius);

    std::shared_ptr<GLTools::Texture> getTexture(const std::string &name);

private:
    GLTools::Camera mCamera;
    GLTools::Sphere mSphere;
    std::unique_ptr<Astronomy::System> mSystem;
    std::unique_ptr<GLTools::Program> mBasicProgram;
    std::map<std::string, std::shared_ptr<GLTools::Texture>> mTextures;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
