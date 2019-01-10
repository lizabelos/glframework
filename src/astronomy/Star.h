// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_STAR_H
#define SOLAR_SYSTEM_STAR_H

#include <string>
#include <ctime>

#include "Astre"
#include "Description"
#include "System"

namespace Astronomy {

    class Star : public Astre {

    public:
        explicit Star(std::string name, description_t description);

        std::string getName() override;
        glm::vec3 getPosition(float time) override;
        glm::vec3 getRotation(float time) override;
        float getDiameter() override;
        glm::vec2 getCenterDistance() override;

        bool hasSystem() override;
        std::shared_ptr<System> getSystem() override;

    private:
        std::string mName;
        description_t mDescription;

        std::shared_ptr<System> mSystem;

    };

}


#endif //SOLAR_SYSTEM_STAR_H
