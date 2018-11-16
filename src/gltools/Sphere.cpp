//
// Created by thomas on 14/11/18.
//

#include "Sphere.h"

#define PI 3.14159265359

GLTools::Sphere::Sphere(unsigned long resolutionX, unsigned long resolutionY) {

    std::shared_ptr<GLTools::SettableVariable> p1 = std::make_shared<SettableVariable>();
    std::shared_ptr<GLTools::SettableVariable> p2 = std::make_shared<SettableVariable>();

    GLTools::Variable cosTheta = cosav(p1 * PI - PI / 2);
    GLTools::Variable sinTheta = sinav(p1 * PI - PI / 2);


    GLTools::Variable x = sinav(p2 * 2 * PI) * cosTheta;
    GLTools::Variable y = sinTheta;
    GLTools::Variable z = cosav(p2 * 2 * PI) * cosTheta;

    GLTools::Variable texX = p1;
    GLTools::Variable texY = p2 * -1 + 1;

    initialize(x, y, z, x, y, z, texX, texY, p1, p2, resolutionX, resolutionY);

}
