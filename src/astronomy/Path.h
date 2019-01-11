//
// Created by thomas on 10/01/19.
//

#ifndef SOLAR_SYSTEM_PATH_H
#define SOLAR_SYSTEM_PATH_H

#include "../maths/Variable"

namespace Astronomy {

    enum PathScaleType {
        NORMAL = 0, LOG = 1, LOGMUL = 2, INDEX = 3
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
