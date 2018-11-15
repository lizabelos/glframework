//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_PLANET_H
#define SOLAR_SYSTEM_PLANET_H

#include <memory>

#include "Astre"
#include "Star"

namespace Astronomy {

    class Planet : public Astre {

    public:
        explicit Planet(std::shared_ptr<Astre> star, std::string name, float radius, float distance, float roationSpeedStar, float rotationSpeed);

        std::string getName() override;
        glm::vec3 getPosition(float time) override;
        glm::vec3 getRotation(float time) override;
        float getRadius() override;

    private:
        std::shared_ptr<Astre> mStar;
        std::string mName;
        float mRadius;
        float mDistance;
        float mRotationSpeedStar;
        float mRotationSpeed;

    };

}


#endif //SOLAR_SYSTEM_PLANET_H
