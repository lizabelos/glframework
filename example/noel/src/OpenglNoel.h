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
#include "gltools/TrackballCamera"
#include "gltools/FreeflyCamera"
#include "glgeometry/Cube.h"
#include "utility/TimeManager"
#include "gltools/TextureManager"
#include "glscene/Scene"



class OpenglNoel : public GLTools::Window {

public:
    OpenglNoel();

protected:
    void render(GLTools::RenderStep renderStep) override;
    void renderDeferred(std::shared_ptr<GLTools::Program> program, glm::vec2 position, glm::vec2 size);
    void keyboard(Uint32 type, bool repeat, int key) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;
    void resize(unsigned int width, unsigned int height) override;
    bool needRenderShadow() override;

private:
    GLGeometry::Sphere mSphere;
    GLGeometry::Cube mCube;
    std::shared_ptr<GLGeometry::Square> mSquare;

    std::shared_ptr<GLTools::FreeflyModelView> mFreeflyCamera, mLightView;
    std::shared_ptr<GLTools::ModelView2D> mModelView2D;


    std::shared_ptr<GLTools::Program> mRender3DProgram, mGeometryProgram, mShadingProgram, mShadingAmbienProgram, mShadingDiffuseProgram, mShadingNormalProgram, mShadingShadowProgram, mShadingSpecularProgram, mShadowProgram;
    std::shared_ptr<GLScene::Scene> mScene;

    GLTools::TextureManager mTextureManager;

    bool mMouseSet;
    bool mSplittedMode;
    glm::vec2 mMouseStart;

};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
