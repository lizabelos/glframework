//
// Created by thomas on 13/11/18.
//

#ifndef OPENGL_NOEL_H
#define OPENGL_NOEL_H

#include <list>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "glgeometry/Sphere"
#include "glgeometry/Circle3D"
#include "gltools/Program"
#include "gltools/Texture"
#include "glgeometry/Square"
#include "gltools/Projection"
#include "gltools/Model"
#include "gltools/FreeflyView"
#include "gltools/LightView"
#include "glgeometry/Cube.h"
#include "utility/TimeManager"
#include "gltools/TextureManager"
#include "glscene/Scene"



class OpenglNoel : public GLTools::Window {

public:
    OpenglNoel();
    void useScene(std::shared_ptr<GLScene::Scene> scene);

protected:
    void render(GLTools::RenderStep renderStep) override;
    void renderDeferred(std::shared_ptr<GLTools::Program> program, glm::vec2 position, glm::vec2 size);
    void renderLight(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep);
    void renderGui(GLTools::RenderStep renderStep);

    void keyboard(Uint32 type, bool repeat, int key) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;
    void resize(unsigned int width, unsigned int height) override;
    bool needRenderShadow() override;

private:
    GLGeometry::Sphere mSphere;
    GLGeometry::Cube mCube;
    GLGeometry::Square mSquare;

    // Model, View, Projection for the camera
    GLTools::PerspectiveProjection mProjection;
    GLTools::Model3D mModel;
    GLTools::FreeflyView mCamera;

    // View, Projection for the shadow
    GLTools::PerspectiveProjection mShadowProjection;
    GLTools::LightView mShadowView;

    // Model for 2D drawing
    GLTools::Model2D mModel2D;


    std::shared_ptr<GLTools::Program> mRender3DProgram, mGeometryProgram, mShadingProgram, mShadingAmbienProgram, mShadingDiffuseProgram, mShadingNormalProgram, mShadingShadowProgram, mShadingSpecularProgram, mShadowProgram;
    std::shared_ptr<GLScene::Scene> mScene;

    GLTools::TextureManager mTextureManager;

    bool mMouseSet;
    bool mSplittedMode;
    glm::vec2 mMouseStart;

    bool mLightToolActive = true;
    bool mCameraLock = false;
    float mLightToolAmbient = 0.3, mLightToolDiffuse = 1.0, mLightToolSpecular = 0.1, mLightToolShadow = 0.5, mLightToolShadowBias = 1.0f;

};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
