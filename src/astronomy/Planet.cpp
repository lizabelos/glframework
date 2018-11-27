//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

#include <iostream>

Astronomy::Planet::Planet(std::shared_ptr<Astronomy::Astre> star, const std::string &name, Astronomy::description_t description) : mStar(star), mName(name), mDescription(description) {

}

std::string Astronomy::Planet::getName() {
    return mName;
}

glm::vec3 Astronomy::Planet::getPosition(float time) {
    return glm::vec4(0, 0, static_cast<float>(mDescription.sunDistance + mStar->getDiameter() / 2), 1) * glm::rotate(glm::mat4(1.0f), static_cast<float>(time * mDescription.orbitalPeriod), glm::vec3(0, 1, 0));
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
