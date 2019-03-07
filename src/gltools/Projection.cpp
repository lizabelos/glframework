//
// Created by belos on 26/02/2019.
//

#include "Projection.h"

GLTools::PerspectiveProjection::PerspectiveProjection(float angle, unsigned int width, unsigned int height, float mNear, float mFar) {
    mProjectionMatrix = glm::perspective(glm::radians(angle), (float)width / (float)height, mNear, mFar);
}

glm::mat4 GLTools::PerspectiveProjection::getMatrix() const {
    return mProjectionMatrix;
}

GLTools::OrthographicProjection::OrthographicProjection(float sceneRadius) {
    mProjectionMatrix = glm::ortho(-sceneRadius, sceneRadius, -sceneRadius, sceneRadius, 0.01f * sceneRadius, 2.f * sceneRadius);
}

glm::mat4 GLTools::OrthographicProjection::getMatrix() const {
    return mProjectionMatrix;
}