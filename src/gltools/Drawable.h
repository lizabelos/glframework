//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_DRAWABLE_H
#define SOLAR_SYSTEM_DRAWABLE_H

#include <vector>

#include "Camera"

namespace GLTools {

    class Drawable {

    public:
        virtual void render(const Camera &camera) const = 0;

    };

}


#endif //SOLAR_SYSTEM_DRAWABLE_H
