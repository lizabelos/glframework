//
// Created by belos on 26/02/2019.
//

#include "Projection.h"

PerspectiveProjection::PerspectiveProjection(unsigned int width, unsigned int height, float mNear = 0.1f, float mFar = 1000.0f) {
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)mWidth / (float)mHeight, mNear, mFar);
}

glm::mat4 PerspectiveProjection::getMatrix() {
    return mProjectionMatrix;
}

OrthographicProjection::OrthographicProjection(float sceneRadius) {
    mProjectionMatrix = glm::ortho(-sceneRadius, sceneRadius, -sceneRadius, sceneRadius, 0.01f * sceneRadius, 2.f * sceneRadius);
}

glm::mat4 OrthographicProjection::getMatrix() {
    return mProjectionMatrix;
}