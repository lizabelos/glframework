//
// Created by thomas on 11/13/18.
//

#include "Star.h"

Astronomy::Star::Star(std::string name, float radius, float rotationSpeed) : mName(name), mRadius(radius) {

}

std::string Astronomy::Star::getName() {
    return mName;
}

glm::vec3 Astronomy::Star::getPosition(time_t time) {
    // todo
    return glm::vec3(0, 0, 0);
}

float Astronomy::Star::getRadius() {
    return mRadius;
}

glm::vec3 Astronomy::Star::getRotation(time_t time) {
    // todo
    return glm::vec3(0, 0, 0);
}
