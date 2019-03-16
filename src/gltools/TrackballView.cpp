//
// Created by belos on 26/02/2019.
//

#include "TrackballView.h"

GLTools::TrackballView::TrackballView() : mFront(50.0f), mLeft(0.0f), mUp(0.0f) {

}

GLTools::TrackballView::TrackballView(float front, float left, float up) : mFront(front), mLeft(left), mUp(up) {

}

glm::mat4 GLTools::TrackballView::getMatrix() const {
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::vec3 xRotation =  glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), (float)(mLeft * 3.14), glm::vec3(0.0f, 1.0f, 0.0f)));
    //if (mTranslate) viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -mFront));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -mFront));
    viewMatrix = glm::rotate(viewMatrix, mLeft * 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, mUp * 3.14f, xRotation);
    return viewMatrix;
}

void GLTools::TrackballView::moveFront(float delta) {
    mFront *= delta;
}

void GLTools::TrackballView::rotateLeft(float delta) {
    mLeft += delta;
}

void GLTools::TrackballView::rotateUp(float delta) {
    mUp += delta;
}

glm::vec3 GLTools::TrackballView::getPosition() const {
    glm::mat4 M = glm::inverse(getMatrix());
    glm::vec3 eyeWorld = glm::vec3(M[0][3], M[1][3], M[2][3]);
    return eyeWorld;
}

void GLTools::TrackballView::setFront(float front) {
    mFront = front;
}
