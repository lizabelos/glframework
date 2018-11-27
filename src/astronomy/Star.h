//
// Created by thomas on 11/13/18.
//

#ifndef SOLAR_SYSTEM_STAR_H
#define SOLAR_SYSTEM_STAR_H

#include <string>
#include <ctime>

#include "Astre"
#include "Description"

namespace Astronomy {

    class Star : public Astre {

    public:
        explicit Star(std::string name, description_t description);

        std::string getName() override;
        glm::vec3 getPosition(float time) override;
        glm::vec3 getRotation(float time) override;
        float getDiameter() override;
        float getCenterDistance() override;

    private:
        std::string mName;
        description_t mDescription;

    };

}


#endif //SOLAR_SYSTEM_STAR_H
