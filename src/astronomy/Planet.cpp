//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

#include <iostream>

Astronomy::Planet::Planet(const std::string &name, Astronomy::description_t description) : mName(name), mDescription(description) {
    mSystem = std::make_shared<Astronomy::System>();
    mMajor = description.sunDistance;
    mMinor = sqrt(mMajor * (1 - (description.orbitalEccentricity * description.orbitalEccentricity)));
}

std::string Astronomy::Planet::getName() {
    return mName;
}

glm::vec3 Astronomy::Planet::getPosition(float time) {

    time = time * 100.0f;

    float x = mMinor * cos(time);
    float y = mMajor * sin(time);

    return glm::vec3(x, 0, y);
}

float Astronomy::Planet::getDiameter() {
    return static_cast<float>(mDescription.diameter);
}

glm::vec3 Astronomy::Planet::getRotation(float time) {
    return glm::vec3(0, 0, 0);
}

glm::vec2 Astronomy::Planet::getCenterDistance() {
    return glm::vec2(mMinor, mMajor);
}

bool Astronomy::Planet::hasSystem() {
    return true;
}

std::shared_ptr<Astronomy::System> Astronomy::Planet::getSystem() {
    return mSystem;
}
