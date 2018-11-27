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
#include "astronomy/Star"
#include "glgeometry/Triangle"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void resize(unsigned int width, unsigned int height) override;
    void render(GLTools::RenderStep renderStep) override;
    void renderSystem(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::System> system, int recursivity);

    glm::vec3 translationScale(glm::vec3 translation, int i);
    float radiusScale(float radius);

    std::shared_ptr<GLTools::Texture> getTexture(const std::string &name);

    void scroll(int x, int y) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;

private:
    GLTools::Camera3D mCamera3D;
    GLTools::Camera2D mCamera2D;
    GLGeometry::Sphere mSphere;
    GLGeometry::Triangle mTriangle;

    std::shared_ptr<Astronomy::Star> mStarSystem;
    std::map<std::string, std::shared_ptr<Astronomy::Astre>> mAstres;

    std::shared_ptr<GLTools::Program> mRender3DProgram, mSelection3DProgram, mRender2DProgram, mSelection2DProgram;
    std::map<std::string, std::shared_ptr<GLTools::Texture>> mTextures;

    float mZoom;
    float mRotationX, mRotationY;

    bool mMouseRotation;
    glm::vec2 mMouseStart;

    bool mProportionalView;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
