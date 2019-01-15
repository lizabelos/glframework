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
#include "astronomy/System"
#include "astronomy/Planet"
#include "astronomy/Star"
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
    void keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;

private:
    GLGeometry::Sphere mSphere;
    GLGeometry::Cube mCube;

    GLTools::FreeflyCamera mFreeflyCamera;

    std::shared_ptr<GLTools::Program> mRender3DProgram, mBackgroundProgram;
    std::shared_ptr<GLScene::Scene> mScene;

    std::shared_ptr<GLTools::TextureCubeMap> mBackground;

    GLTools::TextureManager mTextureManager;

    bool mMouseSet;
    glm::vec2 mMouseStart;

};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
