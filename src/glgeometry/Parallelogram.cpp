//
// Created by thomas on 26/12/18.
//

#include "Parallelogram.h"

GLGeometry::Parallelogram::Parallelogram(unsigned int code) : Drawable(code), mSquare(code), mTriangle(code) {

}

void GLGeometry::Parallelogram::render(GLTools::Camera<glm::vec2> &camera, std::shared_ptr<GLTools::Program> program,
                                       GLTools::RenderStep renderStep) const {

    mSquare.render(camera, program, renderStep);

    camera.pushMatrix();
    camera.translate(glm::vec2(-1, 0));
    mTriangle.render(camera, program, renderStep);
    camera.popMatrix();

    camera.pushMatrix();
    camera.translate(glm::vec2(1, 0));
    camera.rotate(M_PIf32, glm::vec2(1,1));
    mTriangle.render(camera, program, renderStep);
    camera.popMatrix();

}

