//
// Created by thomas on 10/01/19.
//

#ifndef SOLAR_SYSTEM_ELLIPSE3D_H
#define SOLAR_SYSTEM_ELLIPSE3D_H


#include "ParametricDrawable"

namespace GLGeometry {

    class Circle3D : public ParametricDrawable3D {

    public:
        Circle3D(unsigned int code, unsigned long resolution, bool onlyBorder = false, float ring = 0.0f);

    };

}

#endif //SOLAR_SYSTEM_ELLIPSE3D_H
