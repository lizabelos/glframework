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
        explicit Planet(std::shared_ptr<Astre> star, std::string name, float radius);

        std::string getName() override;
        glm::vec3 getPosition(time_t time) override;
        float getRadius() override;

    private:
        std::shared_ptr<Astre> mStar;
        std::string mName;
        float mRadius;

    };

}


#endif //SOLAR_SYSTEM_PLANET_H
