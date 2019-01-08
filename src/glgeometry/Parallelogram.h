//
// Created by thomas on 26/12/18.
//

#ifndef SOLAR_SYSTEM_PARALLELOGRAM_H
#define SOLAR_SYSTEM_PARALLELOGRAM_H

#include "../gltools/Drawable"
#include "Square"
#include "Triangle"

namespace GLGeometry {

    /**
     * 2D Parallelogram
     */
    class Parallelogram : public GLTools::Drawable<glm::vec2> {

    public:
        explicit Parallelogram(unsigned int code);

        void render(GLTools::Camera<glm::vec2> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

    private:
        Square mSquare;
        Triangle mTriangle;

    };

}


#endif //SOLAR_SYSTEM_PARALLELOGRAM_H
