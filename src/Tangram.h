//
// Created by thomas on 11/26/18.
//

#ifndef TANGRAM_TANGRAM_H
#define TANGRAM_TANGRAM_H

#include "gltools/Window"
#include "gltools/Camera"
#include "glgeometry/Circle"
#include "glgeometry/Triangle"


class Tangram : public GLTools::Window {

public:
    Tangram();

    void render(GLTools::RenderStep renderStep) override;

protected:
    void resize(unsigned int width, unsigned int height) override;
    void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) override;
    void mouseMove(glm::vec2 mousePosition, unsigned int selection) override;

private:
    GLTools::Camera2D mCamera;
    std::vector<GLTools::TranslatedDrawable<glm::vec2>> drawables;

    std::shared_ptr<GLTools::Program> mRenderProgram, mSelectionProgram;

    bool mMouseMovement;
    unsigned int mMouseSelection;
    glm::vec2 mMouseStart;
};


#endif //TANGRAM_TANGRAM_H
