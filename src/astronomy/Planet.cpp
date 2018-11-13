//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

Astronomy::Planet::Planet(std::shared_ptr<Astronomy::Astre> star, std::string name, float radius) : mStar(star), mName(name), mRadius(radius) {

}

std::string Astronomy::Planet::getName() {
    return mName;
}

glm::vec3 Astronomy::Planet::getPosition(time_t time) {
    // todo
    return glm::vec3(0, 0, 0);
}

float Astronomy::Planet::getRadius() {
    return mRadius;
}

glm::vec3 Astronomy::Planet::getRotation(time_t time) {
    // todo
    return glm::vec3(0, 0, 0);
}
