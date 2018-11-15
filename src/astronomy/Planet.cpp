//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

#include <iostream>

Astronomy::Planet::Planet(std::shared_ptr<Astronomy::Astre> star, std::string name, float radius, float distance, float roationSpeedStar, float rotationSpeed)
: mStar(star), mName(name), mRadius(radius), mDistance(distance), mRotationSpeedStar(roationSpeedStar), mRotationSpeed(rotationSpeed) {

}

std::string Astronomy::Planet::getName() {
    return mName;
}

glm::vec3 Astronomy::Planet::getPosition(float time) {
    return glm::vec4(0, 0, mDistance, 1) * glm::rotate(glm::mat4(1.0f), time * mRotationSpeedStar, glm::vec3(0, 1, 0));
}

float Astronomy::Planet::getRadius() {
    return mRadius;
}

glm::vec3 Astronomy::Planet::getRotation(float time) {
    return glm::vec3(0, 0, 0);
}
