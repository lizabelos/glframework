//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SYSTEM_H
#define SOLAR_SYSTEM_SYSTEM_H

#include <list>
#include <memory>

#include "Astre"
#include "Star"

namespace Astronomy {

    /***
     * A planetary system is a set of gravitationally bound non-stellar objects in or out of orbit around a star or star system. (Wikipedia)
     */
    class System {

    public:
        explicit System(std::shared_ptr<Star> star);

        std::shared_ptr<Star> getStar();
        std::list<std::shared_ptr<Astre>> getAstres();
        std::list<std::shared_ptr<Astre>> getAll();

        void add(std::shared_ptr<Astre> mAstre);

    private:
        std::shared_ptr<Star> mStar;
        std::list<std::shared_ptr<Astre>> mAstres;


    };

}


#endif //SOLAR_SYSTEM_SYSTEM_H
