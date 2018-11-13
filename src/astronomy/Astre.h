//
// Created by thomas on 11/13/18.
//

#ifndef SOLAR_SYSTEM_ASTRE_H
#define SOLAR_SYSTEM_ASTRE_H


#include <string>

#include <glm/ext.hpp>

namespace Astronomy {

    class Astre {

    public:
        virtual std::string getName() = 0;
        virtual glm::vec3 getPosition(time_t time) = 0;

    };

}


#endif //SOLAR_SYSTEM_ASTRE_H
