//
// Created by thomas on 06/11/18.
//

#include "Camera.h"

GLTools::Camera::Camera() {
    resize(1,1);
    mMVMatrix = glm::mat4(1.0f);
}

GLTools::Camera::Camera(unsigned int width, unsigned int height) {
    resize(width, height);
    mMVMatrix = glm::mat4(1.0f);
}

void GLTools::Camera::resize(unsigned int width, unsigned int height) {
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)width / (float)height, 0.1f, 100.0f);
}

glm::mat4 GLTools::Camera::getProjectionMatrix() const {
    return mProjectionMatrix;
}

glm::mat4 GLTools::Camera::getMVMatrix() const {
    return mMVMatrix;
}

glm::mat4 GLTools::Camera::getNormalMatrix() const {
    return glm::transpose(glm::inverse(mMVMatrix));
}

void GLTools::Camera::pushMatrix() {
    mMVMatrixStack.push_back(mMVMatrix);
}

void GLTools::Camera::popMatrix() {
    mMVMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::Camera::translate(glm::vec3 translation) {
    mMVMatrix = glm::translate(mMVMatrix, translation);
}

void GLTools::Camera::rotate(float angle, glm::vec3 axis) {
    mMVMatrix = glm::rotate(mMVMatrix, angle, axis);
}


void GLTools::Camera::scale(glm::vec3 scaling) {
    mMVMatrix = glm::scale(mMVMatrix, scaling);
}

void GLTools::Camera::scale(float scaling) {
    mMVMatrix = glm::scale(mMVMatrix, glm::vec3(scaling, scaling, scaling));
}

void GLTools::Camera::identity() {
    mMVMatrix = glm::mat4(1.0f);
}

