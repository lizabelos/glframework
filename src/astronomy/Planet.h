//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_PLANET_H
#define SOLAR_SYSTEM_PLANET_H

#include <memory>

#include "Astre"
#include "Star"
#include "Description"
#include "System"

namespace Astronomy {

    class Planet : public Astre {

    public:
        explicit Planet(const std::string &name, description_t description);

        std::string getName() override;
        glm::vec3 getPosition(float time) override;
        glm::vec3 getRotation(float time) override;
        float getDiameter() override;
        float getCenterDistance() override;

        bool hasSystem() override;
        std::shared_ptr<System> getSystem() override;

    private:
        std::string mName;
        description_t mDescription;

        std::shared_ptr<System> mSystem;
    };

}


#endif //SOLAR_SYSTEM_PLANET_H
