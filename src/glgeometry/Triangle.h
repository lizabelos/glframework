//
// Created by thomas on 11/26/18.
//

#ifndef TANGRAM_TRIANGLE_H
#define TANGRAM_TRIANGLE_H

#include "../gltools/Drawable"
#include "Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"

namespace GLGeometry {

    class Triangle : public GLTools::Drawable {

    public:
        explicit Triangle(unsigned int code);

        void render(const GLTools::Camera &camera, GLTools::RenderStep renderStep) const override;

    private:
        GLTools::VertexArrayObject mVertexArrayObject;

    };

}


#endif //TANGRAM_TRIANGLE_H
