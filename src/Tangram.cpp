#include <memory>

//
// Created by thomas on 11/26/18.
//

#include "Tangram.h"


Tangram::Tangram() : Window("Tangram"), mCircle(1, 64), mTriangle(2) {
    mBasicProgram = std::make_shared<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
}

void Tangram::render(GLTools::RenderStep renderStep) {
    mCamera.identity();
    mCircle.render(mCamera, mBasicProgram, renderStep);
    mTriangle.render(mCamera, mBasicProgram, renderStep);
}

void Tangram::resize(unsigned int width, unsigned int height) {
    mCamera.resize(width, height);
}

void Tangram::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {

}
