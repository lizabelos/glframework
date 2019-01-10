// Copyright (C) BELOS Thomas. All Rights Reserved.

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

        description_t getDescription() override;

        float getDiameter() override;
        glm::vec2 getCenterDistance() override;

        bool hasSystem() override;
        std::shared_ptr<System> getSystem() override;

    private:
        std::string mName;
        description_t mDescription;

        std::shared_ptr<System> mSystem;

        double mMajor, mMinor;
    };

}


#endif //SOLAR_SYSTEM_PLANET_H
