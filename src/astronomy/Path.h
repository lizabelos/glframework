//
// Created by thomas on 10/01/19.
//

#ifndef SOLAR_SYSTEM_PATH_H
#define SOLAR_SYSTEM_PATH_H

#include "../maths/Variable"

namespace Astronomy {

    enum PathScaleType {
        NORMAL, LOG, LOGMUL, INDEX
    };

    class PathScale {

    public:
        PathScale();

        PathScaleType type;
        Maths::SVariable param;

    };

    class TimePath {

    public:
        TimePath();

        Maths::SVariable time;
        Maths::Variable x, y, z;
        Maths::Variable rotation;
        Maths::CVariable radius;

    };

    class AnglePath {

    public:
        AnglePath();
        Maths::SVariable angle;
        Maths::Variable x, y, z;
        Maths::Variable rotation;
        Maths::CVariable radius;


    };

}


#endif //SOLAR_SYSTEM_PATH_H
