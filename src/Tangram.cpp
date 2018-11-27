#include <memory>

//
// Created by thomas on 11/26/18.
//

#include "Tangram.h"


Tangram::Tangram() : Window("Tangram"), mCircle(1, 64), mTriangle(2) {
    mBasicProgram = std::make_unique<GLTools::Program>("res/shaders/basic2d.vs.glsl", "res/shaders/basic2d.fs.glsl");
}

void Tangram::render(GLTools::RenderStep renderStep) {
    mCamera.identity();
    mBasicProgram->use();
    mBasicProgram->post(mCamera);
    mCircle.render(mCamera, renderStep);
    mTriangle.render(mCamera, renderStep);
}

void Tangram::resize(unsigned int width, unsigned int height) {
    mCamera.resize(width, height);
}

void Tangram::mouseClick(int mouseX, int mouseY, Uint8 state, Uint8 button, unsigned int selection) {

}
