//
// Created by thomas on 11/26/18.
//

#include "Circle.h"
#include <cmath>

GLGeometry::Circle::Circle(unsigned int code, unsigned long resolution) : ParametricDrawable2D(code) {

    Maths::SVariable p1 = Maths::make_SVariable();
    Maths::SVariable p2 = Maths::make_SVariable();

    Maths::Variable cosTheta = cosav(p1 * M_PI);
    Maths::Variable sinTheta = sinav(p1 * M_PI);

    Maths::Variable x = cosTheta * p2;
    Maths::Variable y = sinTheta * p2;
    Maths::CVariable z = Maths::make_CVariable(0.0f);

    initialize(x, y, x, y, p1, p2, resolution, 2);

}
