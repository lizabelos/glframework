//
// Created by belos on 26/02/2019.
//

#include "FreeflyView.h"


#define _USE_MATH_DEFINES
#include <cmath>

GLTools::FreeflyView::FreeflyView() : GLTools::ModelView3D(), mPitch(0.0f), mRoll(0.0f), mYaw(0.0f), mTranslate(true) {

}

glm::mat4 GLTools::FreeflyView::getViewMatrix() const {
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    viewMatrix = glm::rotate(viewMatrix, mPitch, glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, mYaw, glm::vec3(0.0f, 1.0f, 0.0f));
    if (mTranslate) viewMatrix = glm::translate(viewMatrix, mPosition);

    //viewMatrix = glm::rotate(viewMatrix, mPitch, glm::vec3(1.0f, 0.0f, 0.0f));
    //viewMatrix = glm::rotate(viewMatrix, mRoll, glm::vec3(0.0f, 0.0f, 1.0f));

    return viewMatrix;
}

void GLTools::FreeflyView::moveLeft(float t) {
    glm::vec3 mFront = glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), mYaw, glm::vec3(0.0f, 1.0f, 0.0f))) * t;
    mPosition += mFront;
}

void GLTools::FreeflyView::moveFront(float t) {
    glm::vec3 mFront = glm::vec3(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) * glm::rotate(glm::mat4(1.0f), mYaw, glm::vec3(0.0f, 1.0f, 0.0f))) * t;
    mPosition += mFront;
}

void GLTools::FreeflyView::rotateLeft(float t) {
    mYaw = mYaw + t;
}

void GLTools::FreeflyView::rotateUp(float t) {
    mPitch = mPitch - t;
}

void GLTools::FreeflyView::moveUp(float t) {
    mPosition.y = mPosition.y + t;
}

void GLTools::FreeflyView::enableTranslation() {
    mTranslate = true;
}

void GLTools::FreeflyView::disableTranslation() {
    mTranslate = false;
}

glm::vec3 GLTools::FreeflyView::getPosition() {
    return mPosition;
}