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

float Astronomy::Planet::getDiameter() {
    return static_cast<float>(mDescription.diameter);
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

Astronomy::description_t Astronomy::Planet::getDescription() {
    return mDescription;
}
