//
// Created by thomas on 10/01/19.
//

#include "Circle3D.h"

GLGeometry::Circle3D::Circle3D(unsigned int code, unsigned long resolution, bool onlyBorder) : ParametricDrawable3D(code) {

    Maths::SVariable p1 = Maths::make_SVariable();
    Maths::SVariable p2 = Maths::make_SVariable();

    Maths::Variable cosTheta = cosav(p1 * M_PI * 2);
    Maths::Variable sinTheta = sinav(p1 * M_PI * 2);

    Maths::Variable x = cosTheta * p2;
    Maths::Variable y = sinTheta * p2;

    if (onlyBorder) {
        x = cosTheta;
        y = sinTheta;
    }

    Maths::CVariable z = Maths::make_CVariable(0.0f);



    initialize(x, z, y, x, z, y, x, y, p1, p2, resolution, 2);


}
