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
#include "glgeometry/Cube.h"
#include "utility/TimeManager"
#include "gltools/TextureManager"

#define RENDERCODE_BUTTON_PROPVIEW     1
#define RENDERCODE_BUTTON_CAMERAMODE   2
#define RENDERCODE_BUTTON_PLAY         3

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void resize(unsigned int width, unsigned int height) override;
    void render(GLTools::RenderStep renderStep) override;
    void render3d(GLTools::RenderStep renderStep, GLTools::Camera3D &camera);
    void render2d(GLTools::RenderStep renderStep);
    void renderButton(GLTools::RenderStep renderStep, int uId, glm::vec2 position, std::shared_ptr<GLTools::Texture> texture, glm::vec4 color, glm::vec4 hover);
    void renderSystem(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<Astronomy::System> system, int &i, int &subi, int &mousei);
    void renderAstre(GLTools::RenderStep renderStep, GLTools::Camera3D &camera, std::shared_ptr<Astronomy::Astre> astre, int &i, int &subi, int &mousei);
    std::shared_ptr<Astronomy::Astre> searchAstre(std::shared_ptr<Astronomy::Astre> astre, int index, int &i);

    void scroll(int x, int y) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;
    void keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key) override;

private:
    GLTools::TrackballCamera mTrackballCamera;
    GLTools::FreeflyCamera mFreeflyCamera;
    GLTools::Camera2D mCamera2D;
    GLGeometry::Sphere mSphere;
    GLGeometry::Circle3D mCircle3D, mRing3D;
    GLGeometry::Square mSquare;
    GLGeometry::Cube mCube;
    GLGeometry::ParametricDrawable3D mDynamicOrbit;

    std::shared_ptr<Astronomy::Star> mStarSystem;
    std::shared_ptr<Astronomy::Astre> mCurrentSystem;
    std::map<std::string, std::shared_ptr<Astronomy::Astre>> mAstres;

    std::shared_ptr<GLTools::Program> mRender3DProgram, mLine3DProgram, mSelection3DProgram, mRender2DProgram, mSelection2DProgram, mBackgroundProgram, mLightProgram, mLightNightProgram, mRingProgram;


    GLTools::TextureManager mPlanetDayTexture, mPlanetNightTexture, mRingColorTexture, mRingAlphaTexture;

    std::shared_ptr<GLTools::Texture> mTextureProp, mTexturePlay, mTextureCamera;
    std::shared_ptr<GLTools::TextureCubeMap> mBackground;

    Astronomy::PathScaleType mScaleType;

    TimeManager mTimeManager;

    bool mMouseRotation;
    glm::vec2 mMouseStart;

    bool mFreefly;

    int selectionHover;
};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
