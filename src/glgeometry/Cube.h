//
// Created by thomas on 12/01/19.
//

#ifndef SOLAR_SYSTEM_CUBE_H
#define SOLAR_SYSTEM_CUBE_H

#include "../gltools/Drawable"
#include "../maths/Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"

namespace GLGeometry {

    class Cube : public GLTools::Drawable<glm::vec3> {

    public:
        explicit Cube(unsigned int code);

        void render(GLTools::Camera<glm::vec3> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

    private:
        GLTools::VertexArrayObject mVertexArrayObject;
        int mSize;

    };

}


#endif //SOLAR_SYSTEM_CUBE_H
