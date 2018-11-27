//
// Created by thomas on 11/13/18.
//

#include "Star.h"

Astronomy::Star::Star(std::string name, description_t description) : mName(name), mDescription(description) {

}

std::string Astronomy::Star::getName() {
    return mName;
}

glm::vec3 Astronomy::Star::getPosition(float time) {
    // todo
    return glm::vec3(0, 0, 0);
}

float Astronomy::Star::getDiameter() {
    return static_cast<float>(mDescription.diameter);
}

glm::vec3 Astronomy::Star::getRotation(float time) {
    // todo
    return glm::vec3(0, 0, 0);
}
