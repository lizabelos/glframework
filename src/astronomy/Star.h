//
// Created by thomas on 11/13/18.
//

#ifndef SOLAR_SYSTEM_STAR_H
#define SOLAR_SYSTEM_STAR_H

#include <string>
#include <ctime>

#include "Astre"

namespace Astronomy {

    class Star : public Astre {

    public:
        explicit Star(std::string name, float radius);

        std::string getName() override;
        glm::vec3 getPosition(time_t time) override;
        float getRadius() override;

    private:
        std::string mName;
        float mRadius;

    };

}


#endif //SOLAR_SYSTEM_STAR_H
