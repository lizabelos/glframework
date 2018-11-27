//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_DRAWABLE_H
#define SOLAR_SYSTEM_DRAWABLE_H

#include <vector>

#include "Camera"

namespace GLTools {

    typedef enum RenderStep {
        RENDER_SCREEN, RENDER_SELECTION
    } RenderStep;

    class Drawable {

    public:
        explicit Drawable(unsigned int code);

        virtual void render(const Camera &camera, RenderStep renderStep) const = 0;

        unsigned int getCode();
        bool is(float code);

    private:
        unsigned int mCode;

    };

}


#endif //SOLAR_SYSTEM_DRAWABLE_H
