//
// Created by thomas on 14/11/18.
//

#ifndef SOLAR_SYSTEM_SPHERE_H
#define SOLAR_SYSTEM_SPHERE_H

#include "ParametricDrawable"

namespace GLGeometry {

    class Sphere : public ParametricDrawable {

    public:
        Sphere(unsigned int code, unsigned long resolutionX, unsigned long resolutionY);

    };

}


#endif //SOLAR_SYSTEM_SPHERE_H
