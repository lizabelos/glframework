//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"

#define PI 3.14159265359

GLTools::Sphere::Sphere(unsigned long resolutionX, unsigned long resolutionY) {

    std::shared_ptr<GLTools::SettableVariable> p1 = std::make_shared<SettableVariable>();
    std::shared_ptr<GLTools::SettableVariable> p2 = std::make_shared<SettableVariable>();

    GLTools::Variable u = p1 * (2 * PI);
    GLTools::Variable v = p2 * (2 * PI);

    GLTools::Variable x = cosav(u) * cosav(v);
    GLTools::Variable y = sinav(u) * cosav(v);
    GLTools::Variable z = sinav(v);

    initialize(x, y, z, x, y, z, p1, p2, p1, p2, resolutionX, resolutionY);

}
