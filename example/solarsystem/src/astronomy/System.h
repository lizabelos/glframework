// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_SYSTEM_H
#define SOLAR_SYSTEM_SYSTEM_H

#include <vector>
#include <memory>

#include "Astre"
#include "Star"

namespace Astronomy {

    /***
     * A planetary system is a set of gravitationally bound non-stellar objects in or out of orbit around a star or star system. (Wikipedia)
     */
    class System {

    public:
        System();

        std::vector<std::shared_ptr<Astre>> getAstres();
        void add(std::shared_ptr<Astre> mAstre);

    private:
        std::vector<std::shared_ptr<Astre>> mAstres;


    };

}


#endif //SOLAR_SYSTEM_SYSTEM_H
