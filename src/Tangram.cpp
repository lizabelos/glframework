#include <memory>

//
// Created by thomas on 11/26/18.
//

#include "Tangram.h"


Tangram::Tangram() : Window("Tangram"), mMouseMovement(false) {
    mRenderProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
    mSelectionProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");
    drawables.emplace_back(GLTools::TranslatedDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0), glm::vec2(0.0f, 0.0f)));
    drawables.emplace_back(GLTools::TranslatedDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0), glm::vec2(0.0f, 0.0f)));
}

void Tangram::render(GLTools::RenderStep renderStep) {
    std::shared_ptr<GLTools::Program> program;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            program = mRenderProgram;
            break;
        case GLTools::RENDER_SELECTION:
            program = mSelectionProgram;
            break;
    }

    mCamera.identity();
    mCamera.scale(glm::vec2(0.3f, 0.3f));
    int i = 0;
    for (const GLTools::TranslatedDrawable<glm::vec2> &drawable : drawables) {
        program->post("uId", i + 1);
        drawable.render(mCamera, program, renderStep);
        i++;
    }
}

void Tangram::resize(unsigned int width, unsigned int height) {
    mCamera.resize(width, height);
}

void Tangram::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {
    int id = selection - 1;
    if (id < drawables.size() && state == SDL_PRESSED && !mMouseMovement) {
        mMouseMovement = true;
        mMouseSelection = id;
        mMouseStart = mousePosition;
    }

    if (state == SDL_RELEASED) {
        mMouseMovement = false;
    }
}

void Tangram::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    if (mMouseMovement) {
        glm::vec2 diff = mousePosition - mMouseStart;
        diff.y = -diff.y;
        diff = diff * 2.0f / 0.3f;

        mMouseStart = mousePosition;
        drawables[mMouseSelection].move(diff);
    }

}
