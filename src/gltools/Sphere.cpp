//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"

#define PI 3.14159265359

GLTools::Sphere::Sphere(unsigned long resolutionX, unsigned long resolutionY) {

    GLTools::SVariable p1 = GLTools::make_SVariable();
    GLTools::SVariable p2 = GLTools::make_SVariable();

    GLTools::Variable cosTheta = cosav(p1 * PI - PI / 2);
    GLTools::Variable sinTheta = sinav(p1 * PI - PI / 2);


    GLTools::Variable x = sinav(p2 * 2 * PI) * cosTheta;
    GLTools::Variable y = sinTheta;
    GLTools::Variable z = cosav(p2 * 2 * PI) * cosTheta;

    GLTools::Variable texY = p1;
    GLTools::Variable texX = p2 * -1 + 1;

    initialize(x, y, z, x, y, z, texX, texY, p1, p2, resolutionX, resolutionY);

}
