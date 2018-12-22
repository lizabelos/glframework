//
// Created by thomas on 11/26/18.
//

#ifndef TANGRAM_TANGRAM_H
#define TANGRAM_TANGRAM_H

#include "gltools/Window"
#include "gltools/Camera"
#include "gltools/Texture"
#include "glgeometry/Circle"
#include "glgeometry/Triangle"
#include "glgeometry/Square"


class Tangram : public GLTools::Window {

public:
    Tangram();

    void render(GLTools::RenderStep renderStep) override;

protected:
    void resize(unsigned int width, unsigned int height) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;

    void roundObject(GLTools::TransformDrawable<glm::vec2> &transformDrawable);

private:
    GLTools::Camera2D mCamera;
    std::vector<GLTools::TransformDrawable<glm::vec2>> drawables;
    GLGeometry::Square mSquare;

    std::shared_ptr<GLTools::Program> mRenderProgram, mShadowProgram, mSelectionProgram;
    std::shared_ptr<GLTools::Texture> mTextureWood;

    bool mMouseMovement;
    int mMouseSelection;
    glm::vec2 mMouseStart;

    const float SCALE = 0.2f;
    const float UNIT = 0.5f * SCALE;
    const float ROUND = UNIT;
};


#endif //TANGRAM_TANGRAM_H
