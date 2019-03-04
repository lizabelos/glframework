//
// Created by belos on 26/02/2019.
//

#include "LightView.h"


GLTools::LightView::LightView() : LightView(glm::vec3(0,0,0), 1, 0, 0, glm::vec3(0, -1, 0)) {
}


GLTools::LightView::LightView(glm::vec3 sceneCenter, float sceneRadius, float phi, float theta, glm::vec3 direction) : mLightPosition(sceneCenter), mSceneRadius(sceneRadius), mPhi(phi), mTheta(theta), mDirection(direction) {
    processLightMatrix();
}

glm::mat4 GLTools::LightView::getMatrix() const {
    return mLightMatrix;
}

void GLTools::LightView::processLightMatrix() {

    static const auto computeDirectionVectorUp = [](float phiRadians, float thetaRadians)
    {
        float cosPhi = glm::cos(phiRadians);
        float sinPhi = glm::sin(phiRadians);
        float cosTheta = glm::cos(thetaRadians);
        return -glm::normalize(glm::vec3(sinPhi * cosTheta, -glm::sin(thetaRadians), cosPhi * cosTheta));
    };

    const auto dirLightUpVector = computeDirectionVectorUp(glm::radians(mPhi), glm::radians(mTheta));
    // mLightMatrix = glm::lookAt(mLightPosition + mDirection * mSceneRadius, mLightPosition, dirLightUpVector);
    mLightMatrix = glm::lookAt(mLightPosition, mLightPosition + mDirection * mSceneRadius, dirLightUpVector);
}


void GLTools::LightView::moveLeft(float t) {
    mLightPosition.x = mLightPosition.x + t;
    processLightMatrix();
}

void GLTools::LightView::moveFront(float t) {
    mLightPosition.z = mLightPosition.z + t;
    processLightMatrix();
}

void GLTools::LightView::moveUp(float t) {
    mLightPosition.y = mLightPosition.y + t;
    processLightMatrix();
}

glm::vec3 GLTools::LightView::getLightPosition() const {
    return mLightPosition;
}

void GLTools::LightView::setPhi(float phi) {
    mPhi = phi;
    processLightMatrix();
}

void GLTools::LightView::setTheta(float theta) {
    mTheta = theta;
    processLightMatrix();
}
