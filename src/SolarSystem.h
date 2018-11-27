//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include <list>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "glgeometry/Sphere"
#include "gltools/Program"
#include "gltools/Texture"
#include "astronomy/System"
#include "astronomy/Planet"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void resize(unsigned int width, unsigned int height);
    void render(GLTools::RenderStep renderStep) override;

    glm::vec3 translationScale(glm::vec3 translation, int i);
    float radiusScale(float radius);

    std::shared_ptr<GLTools::Texture> getTexture(const std::string &name);

    void scroll(int x, int y) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;

private:
    GLTools::Camera3D mCamera;
    GLGeometry::Sphere mSphere;
    std::unique_ptr<Astronomy::System> mSystem;
    std::shared_ptr<GLTools::Program> mBasicProgram, mSelectionProgram;
    std::map<std::string, std::shared_ptr<GLTools::Texture>> mTextures;

    float mZoom;
    float rotationX, rotationY;

    bool mouseRotation;
    glm::vec2 mMouseStart;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
