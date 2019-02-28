// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef TANGRAM_TRIANGLE_H
#define TANGRAM_TRIANGLE_H

#include "../gltools/Drawable"
#include "../maths/Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"

namespace GLGeometry {

    /**
     * 2D Triangle
     */
    class Triangle : public GLTools::Drawable<glm::vec2> {

    public:
        explicit Triangle(unsigned int code);

        void render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

    private:
        GLTools::VertexArrayObject mVertexArrayObject;

    };

}


#endif //TANGRAM_TRIANGLE_H
