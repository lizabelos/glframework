// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_SPHERE_H
#define SOLAR_SYSTEM_SPHERE_H

#include "ParametricDrawable"

namespace GLGeometry {

    class Sphere : public ParametricDrawable3D {

    public:
        Sphere(unsigned int code, unsigned long resolutionX, unsigned long resolutionY);

    };

}


#endif //SOLAR_SYSTEM_SPHERE_H
