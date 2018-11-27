//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"
#include <cmath>

GLGeometry::Sphere::Sphere(unsigned int code, unsigned long resolutionX, unsigned long resolutionY) : ParametricDrawable(code) {

    GLGeometry::SVariable p1 = GLGeometry::make_SVariable();
    GLGeometry::SVariable p2 = GLGeometry::make_SVariable();

    GLGeometry::Variable cosTheta = cosav(p1 * M_PI - M_PI / 2);
    GLGeometry::Variable sinTheta = sinav(p1 * M_PI - M_PI / 2);


    GLGeometry::Variable x = sinav(p2 * 2 * M_PI) * cosTheta;
    GLGeometry::Variable y = sinTheta;
    GLGeometry::Variable z = cosav(p2 * 2 * M_PI) * cosTheta;

    GLGeometry::Variable texY = p1;
    GLGeometry::Variable texX = p2 * -1 + 1;

    initialize(x, y, z, x, y, z, texX, texY, p1, p2, resolutionX, resolutionY);

}
