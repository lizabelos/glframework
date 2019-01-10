//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include <list>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "glgeometry/Sphere"
#include "glgeometry/Circle3D"
#include "gltools/Program"
#include "gltools/Texture"
#include "astronomy/System"
#include "astronomy/Planet"
#include "astronomy/Star"
#include "glgeometry/Square"
#include "gltools/TrackballCamera"
#include "gltools/FreeflyCamera"

#define RENDERCODE_BUTTON_PROPVIEW     1
#define RENDERCODE_BUTTON_CAMERAMODE   2
#define RENDERCODE_BUTTON_PLAY         3

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void resize(unsigned int width, unsigned int height) override;
    void render(GLTools::RenderStep renderStep) override;
    void render3d(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<GLTools::Program> program);
    void render2d(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program);
    void renderButton(GLTools::RenderStep renderStep, std::shared_ptr<GLTools::Program> program, int uId, glm::vec2 position, std::shared_ptr<GLTools::Texture> texture, glm::vec4 color, glm::vec4 hover);
    void renderSystem(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::System> system, int &i);
    void renderAstre(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<GLTools::Program> program, std::shared_ptr<Astronomy::Astre> astre, int &i);

    glm::vec3 translationScale(glm::vec3 translation, int i);
    float translationScaleOneAxis(float translation, int i);
    float radiusScale(float radius);

    std::shared_ptr<GLTools::Texture> getTexture(const std::string &name);

    void scroll(int x, int y) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;
    void keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key) override;

private:
    GLTools::TrackballCamera mTrackballCamera;
    GLTools::FreeflyCamera mFreeflyCamera;
    GLTools::Camera2D mCamera2D;
    GLGeometry::Sphere mSphere;
    GLGeometry::Circle3D mCircle3D;
    GLGeometry::Square mSquare;

    std::shared_ptr<Astronomy::Star> mStarSystem;
    std::map<std::string, std::shared_ptr<Astronomy::Astre>> mAstres;

    std::shared_ptr<GLTools::Program> mRender3DProgram, mLine3DProgram, mSelection3DProgram, mRender2DProgram, mSelection2DProgram;
    std::map<std::string, std::shared_ptr<GLTools::Texture>> mTextures;

    std::shared_ptr<GLTools::Texture> mTextureProp, mTexturePlay, mTextureCamera;

    bool mMouseRotation;
    glm::vec2 mMouseStart;

    bool mProportionalView;
    bool mFreefly;
    bool mPlay;

    int selectionHover;
    float lastTime;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
