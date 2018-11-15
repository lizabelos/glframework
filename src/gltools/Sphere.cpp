//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"

#define PI 3.14159265359

GLTools::Sphere::Sphere(unsigned long resolutionX, unsigned long resolutionY) {

    SettableVariable p1, p2;

    AbstractVariable &u = p1 * (2 * PI);
    AbstractVariable &v = p2 * (2 * PI);

    AbstractVariable &x = cosav(u) * cosav(v);
    AbstractVariable &y = sinav(u) * cosav(v);
    AbstractVariable &z = sinav(v);

    AbstractVariable &normX = x;
    AbstractVariable &normY = y;
    AbstractVariable &normZ = z;

    AbstractVariable &texX = p1;
    AbstractVariable &texY = p2;

    initialize(x, y, z, normX, normY, normZ, texX, texY, p1, p2, resolutionX, resolutionY);

}
