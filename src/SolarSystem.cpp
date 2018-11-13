//
// Created by thomas on 13/11/18.
//

#include "SolarSystem.h"

SolarSystem::SolarSystem() : GLTools::Window("Solar System") {

}

void SolarSystem::render() {

    time_t currentTime;
    time(&currentTime);

    for (const std::pair<std::shared_ptr<Astronomy::Astre>, std::shared_ptr<GLTools::Drawable>> &astreDrawable : mAstresDrawable) {

        std::shared_ptr<Astronomy::Astre> astre = astreDrawable.first;
        std::shared_ptr<GLTools::Drawable> drawable = astreDrawable.second;

        mCamera.pushMatrix();

        mCamera.scale(radiusScale(astre->getRadius()));
        mCamera.rotate(astre->getRotation(currentTime));
        mCamera.translate(translationScale(astre->getPosition(currentTime)));

        drawable->render(mCamera);

        mCamera.popMatrix();

    }

}

glm::vec3 SolarSystem::translationScale(glm::vec3 translation) {
    return translation / 100.0f;
}

float SolarSystem::radiusScale(float radius) {
    return radius / 10.0f;
}

void SolarSystem::add(std::shared_ptr<Astronomy::Astre> astre) {
    // todo
}
