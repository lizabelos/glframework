//
// Created by belos on 26/02/2019.
//

#include "LightView.h"


GLTools::LightView::LightView() : LightView(glm::vec3(0,0,0)) {
}


GLTools::LightView::LightView(glm::vec3 position) : mLightPosition(position) {
    processLightMatrix();
}

std::vector<glm::mat4> GLTools::LightView::getMatrices() const {
    return mLightMatrices;
}

void GLTools::LightView::processLightMatrix() {

    mLightMatrices.clear();
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
    mLightMatrices.push_back(glm::lookAt(mLightPosition, mLightPosition + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));


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
