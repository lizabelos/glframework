// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_ASTRE_H
#define SOLAR_SYSTEM_ASTRE_H


#include <string>
#include <memory>

#include <glm/ext.hpp>

namespace Astronomy {

    class System;

    class Astre {

    public:
        virtual std::string getName() = 0;
        virtual glm::vec3 getPosition(float time) = 0;
        virtual glm::vec3 getRotation(float time) = 0;
        virtual float getCenterDistance() = 0;
        virtual float getDiameter() = 0;

        virtual bool hasSystem() = 0;
        virtual std::shared_ptr<System> getSystem() = 0;

    };

}


#endif //SOLAR_SYSTEM_ASTRE_H
