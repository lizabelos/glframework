#include <memory>

//
// Created by thomas on 11/26/18.
//

#include "Tangram.h"


Tangram::Tangram() : Window("Tangram"), mMouseMovement(false) {
    mRenderProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
    mSelectionProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");

    int bigTriangle = 2, mediumTriangle = 1, smallTriangle = 2, square = 1;

    for (int i = 0; i < bigTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(1.5f, 1.5f));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < mediumTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(1.0f, 1.0f));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < smallTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(0.75f, 0.75f));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < square; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Square>(0));
        transformDrawable.scale(glm::vec2(1.0f, 1.0f));
        drawables.emplace_back(transformDrawable);
    }

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
    mCamera.scale(glm::vec2(0.2f, 0.2f));
    int i = 0;
    for (const GLTools::TransformDrawable<glm::vec2> &drawable : drawables) {

        float r = 0, g = 0, b = 0;
        for (int j = 2; j < 5; j++) {
            r += (float)((i + 0) % j) / (float)(3 * (j - 1));
            g += (float)((i + 1) % j) / (float)(3 * (j - 1));
            b += (float)((i + 2) % j) / (float)(3 * (j - 1));
        }

        program->post("uId", i + 1);
        program->post("uColor", glm::vec4(r, g, b, 1.0f));
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
        diff = diff * 2.0f;

        mMouseStart = mousePosition;
        drawables[mMouseSelection].move(diff);
    }

}
