//
// Created by belos on 26/02/2019.
//

#include "Projection.h"

#include <iostream>

GLTools::PerspectiveProjection::PerspectiveProjection(float angle, unsigned int width, unsigned int height, float mNear, float mFar) {
    std::cout << "PerspectiveProjection(angle = " << angle << ",width=" << width << ",height=" << height << ",near=" << mNear << ",far=" << mFar << std::endl;
    if (mNear > mFar) {
        throw std::runtime_error("mNear > mFar");
    }
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