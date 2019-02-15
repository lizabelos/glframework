//
// Created by thomas on 11/13/18.
//

#include "Star.h"

Astronomy::Star::Star(std::string name, description_t description) : mName(name), mDescription(description) {
    mSystem = std::make_shared<Astronomy::System>();
}

std::string Astronomy::Star::getName() {
    return mName;
}

float Astronomy::Star::getDiameter() {
    return static_cast<float>(mDescription.diameter);
}

glm::vec2 Astronomy::Star::getCenterDistance() {
    return glm::vec2(0, 0);
}

bool Astronomy::Star::hasSystem() {
    return true;
}

std::shared_ptr<Astronomy::System> Astronomy::Star::getSystem() {
    return mSystem;
}

Astronomy::description_t Astronomy::Star::getDescription() {
    return mDescription;
}

Astronomy::TimePath Astronomy::Star::getTimePath(Astronomy::PathScale scale) {
    Astronomy::TimePath path;

    if (mDescription.rotationPeriod == 0) {
        path.rotation = Maths::make_CVariable(0.0f);
    } else {
        path.rotation = path.time * 100000.0f / mDescription.rotationPeriod;
    }

    path.x = Maths::make_CVariable(0.0f);
    path.y = Maths::make_CVariable(0.0f);
    path.z = Maths::make_CVariable(0.0f);

    switch (scale.type) {
        case NORMAL:
            path.radius = Maths::make_CVariable(static_cast<float>(mDescription.diameter / (2.0f * NORMAL_SIZE_SCALE)));
            break;
        case LOG:
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case LOGMUL:
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case INDEX:
            path.radius = Maths::make_CVariable(1.0f);
            break;
    }

    return path;
}

Astronomy::AnglePath Astronomy::Star::getAnglePath(Astronomy::PathScale scale) {
    Astronomy::AnglePath path;

    path.rotation = Maths::make_CVariable(0.0f);

    path.x = Maths::make_CVariable(0.0f);
    path.y = Maths::make_CVariable(0.0f);
    path.z = Maths::make_CVariable(0.0f);

    switch (scale.type) {
        case NORMAL:
            path.radius = Maths::make_CVariable(static_cast<float>(mDescription.diameter / (2.0f * NORMAL_SIZE_SCALE)));
            break;
        case LOG:
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case LOGMUL:
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case INDEX:
            path.radius = Maths::make_CVariable(1.0f);
            break;
    }

    return path;
}
