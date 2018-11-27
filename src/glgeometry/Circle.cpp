//
// Created by thomas on 11/26/18.
//

#include "Circle.h"
#include <cmath>

GLGeometry::Circle::Circle(unsigned int code, unsigned long resolution) : ParametricDrawable(code) {

    GLGeometry::SVariable p1 = GLGeometry::make_SVariable();
    GLGeometry::SVariable p2 = GLGeometry::make_SVariable();

    GLGeometry::Variable cosTheta = cosav(p1 * M_PI);
    GLGeometry::Variable sinTheta = sinav(p1 * M_PI);

    GLGeometry::Variable x = cosTheta * p2;
    GLGeometry::Variable y = sinTheta * p2;
    GLGeometry::CVariable z = GLGeometry::make_CVariable(0.0f);

    initialize(x, y, z, x, y, z, x, y, p1, p2, resolution, 2);

}
