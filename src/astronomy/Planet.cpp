//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

#include <iostream>

Astronomy::Planet::Planet(const std::string &name, Astronomy::description_t description) : mName(name), mDescription(description) {
    mSystem = std::make_shared<Astronomy::System>();
}

std::string Astronomy::Planet::getName() {
    return mName;
}

glm::vec3 Astronomy::Planet::getPosition(float time) {
    return glm::vec4(0, 0, static_cast<float>(mDescription.sunDistance), 1) * glm::rotate(glm::mat4(1.0f), static_cast<float>(time * mDescription.orbitalPeriod), glm::vec3(0, 1, 0));
}

float Astronomy::Planet::getDiameter() {
    return static_cast<float>(mDescription.diameter);
}

glm::vec3 Astronomy::Planet::getRotation(float time) {
    return glm::vec3(0, 0, 0);
}

float Astronomy::Planet::getCenterDistance() {
    return mDescription.sunDistance;
}

bool Astronomy::Planet::hasSystem() {
    return true;
}

std::shared_ptr<Astronomy::System> Astronomy::Planet::getSystem() {
    return mSystem;
}
