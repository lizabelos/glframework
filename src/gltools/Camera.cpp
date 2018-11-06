//
// Created by thomas on 06/11/18.
//

#include "Camera.h"

GLTools::Camera::Camera() {
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)(800.0 / 600.0), 0.1f, 100.0f);
}

glm::mat4 GLTools::Camera::getProjectionMatrix() {
    return mProjectionMatrix;
}

glm::mat4 GLTools::Camera::getMVMatrix() {
    return mMVMatrix;
}

glm::mat4 GLTools::Camera::getNormalMatrix() {
    return mNormalMatrix;
}