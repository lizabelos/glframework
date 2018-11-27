//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_PLANET_H
#define SOLAR_SYSTEM_PLANET_H

#include <memory>

#include "Astre"
#include "Star"
#include "Description"

namespace Astronomy {

    class Planet : public Astre {

    public:
        explicit Planet(std::shared_ptr<Astre> star, const std::string &name, description_t description);

        std::string getName() override;
        glm::vec3 getPosition(float time) override;
        glm::vec3 getRotation(float time) override;
        float getDiameter() override;

    private:
        std::shared_ptr<Astre> mStar;
        std::string mName;
        description_t mDescription;

    };

}


#endif //SOLAR_SYSTEM_PLANET_H
