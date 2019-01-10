//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"
#include <cmath>

GLGeometry::Sphere::Sphere(unsigned int code, unsigned long resolutionX, unsigned long resolutionY) : ParametricDrawable3D(code) {

    Maths::SVariable p1 = Maths::make_SVariable();
    Maths::SVariable p2 = Maths::make_SVariable();

    Maths::Variable cosTheta = cosav(p1 * M_PI - M_PI / 2);
    Maths::Variable sinTheta = sinav(p1 * M_PI - M_PI / 2);


    Maths::Variable x = sinav(p2 * 2 * M_PI) * cosTheta;
    Maths::Variable y = sinTheta;
    Maths::Variable z = cosav(p2 * 2 * M_PI) * cosTheta;

    Maths::Variable texY = p1;
    Maths::Variable texX = p2 * -1 + 1;

    initialize(x, y, z, x, y, z, texX, texY, p1, p2, resolutionX, resolutionY);

}
