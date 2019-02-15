#include <iostream>
#include <memory>

//
// Created by thomas on 11/26/18.
//

#include "Tangram.h"


Tangram::Tangram() : Window("tangram"), mMouseMovement(false), mSquare(0), mNeedRender(true) {
    mRenderProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/button2d.fs.glsl");
    mShadowProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
    mSelectionProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/selection2d.fs.glsl");

    mTextureWood = std::make_shared<GLTools::Texture>("res/wood.jpg");

    int bigTriangle = 2, mediumTriangle = 1, smallTriangle = 2, square = 1, parallelogram = 1;

    for (int i = 0; i < bigTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(UNIT * 4, UNIT * 4));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < mediumTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(UNIT * 2, UNIT * 2));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < smallTriangle; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Triangle>(0));
        transformDrawable.scale(glm::vec2(UNIT * 1, UNIT * 1));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < square; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Square>(0));
        transformDrawable.scale(glm::vec2(UNIT * 2, UNIT * 2));
        drawables.emplace_back(transformDrawable);
    }

    for (int i = 0; i < parallelogram; i++) {
        GLTools::TransformDrawable<glm::vec2> transformDrawable = GLTools::TransformDrawable<glm::vec2>(std::make_shared<GLGeometry::Parallelogram>(0));
        transformDrawable.scale(glm::vec2(UNIT * 2, UNIT * 2));
        drawables.emplace_back(transformDrawable);
    }

}

void Tangram::render(GLTools::RenderStep renderStep) {
    std::shared_ptr<GLTools::Program> program;
    switch (renderStep) {

        case GLTools::RENDER_SCREEN:
            program = mRenderProgram;
            mNeedRender = false;
            break;
        case GLTools::RENDER_SELECTION:
            program = mSelectionProgram;
            break;
    }

    mCamera.identity();
    //mCamera.scale(glm::vec2(0.2f, 0.2f));
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
        mTextureWood->activate(GL_TEXTURE0);
        program->postTexture("uTexture", 0);
        drawable.render(mCamera, program, renderStep);

        GLTools::TransformDrawable<glm::vec2> translationRoundedDrawable = drawable;
        roundObject(translationRoundedDrawable);
        program->post("uColor", glm::vec4(r, g, b, 0.2f));
        translationRoundedDrawable.render(mCamera, program, renderStep);

        i++;
    }

    if (renderStep == GLTools::RENDER_SCREEN) {

        int max = static_cast<int>(2.0f / ROUND);
        for (int x = 0; x < max; x++) {
            for (int y = 0; y < max; y++) {
                float color = (float)((x % 2) + (y % 2)) / 2.0f;
                mCamera.pushMatrix();
                mCamera.translate(glm::vec2(x * ROUND - 1.0f,y * ROUND - 1.0f));
                mCamera.scale(glm::vec2(ROUND, ROUND));

                mShadowProgram->post("uColor", glm::vec4(color, color, color, 0.3f));
                mSquare.render(mCamera, mShadowProgram, renderStep);
                mCamera.popMatrix();

            }
        }
    }
}

void Tangram::resize(unsigned int width, unsigned int height) {
    mCamera.resize(width, height);
    mNeedRender = true;
}

void Tangram::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {
    int id = selection;
    id = id - 1;

    if (id < drawables.size() && id >= 0 && state == SDL_PRESSED && button == SDL_BUTTON_LEFT && !mMouseMovement) {
        mMouseMovement = true;
        mMouseSelection = id;
        mMouseStart = mousePosition;
    }

    if (state == SDL_RELEASED && button == SDL_BUTTON_LEFT) {
        mMouseMovement = false;
        roundObject(drawables[mMouseSelection]);
        mNeedRender = true;
    }

    if (id < drawables.size() && id >= 0 && state == SDL_RELEASED && button == SDL_BUTTON_RIGHT) {
        drawables[id].rotate(M_PI / 2, glm::vec2(1.0f, 1.0f));
        mNeedRender = true;
    }

}

void Tangram::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    if (mMouseMovement) {
        glm::vec2 diff = mousePosition - mMouseStart;
        diff.y = -diff.y;
        diff = diff * 2.0f;

        mMouseStart = mousePosition;
        drawables[mMouseSelection].move(diff);
        mNeedRender = true;
    }

}

void Tangram::roundObject(GLTools::TransformDrawable<glm::vec2> &d) {
    glm::vec2 translation = d.getTranslation();
    glm::vec2 scale = d.getScale();

    // Set the center to bottom left;
    translation = translation - scale;

    // Calculate the new position
    translation = glm::vec2(ROUND * roundf(translation.x / ROUND), ROUND * roundf(translation.y / ROUND));

    // Restore the center
    translation = translation + scale;

    d.setTranslation(translation);
}

bool Tangram::waitEvent() {
    return true;
}

bool Tangram::needRender() {
    return mNeedRender;
}
