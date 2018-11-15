#include <memory>

//
// Created by thomas on 11/14/18.
//

#include "ParametricDrawable.h"

void GLTools::ParametricDrawable::initialize(GLTools::AbstractVariable &x, GLTools::AbstractVariable &y,
                                                GLTools::AbstractVariable &z, GLTools::AbstractVariable &normX,
                                                GLTools::AbstractVariable &normY, GLTools::AbstractVariable &normZ,
                                                GLTools::SettableVariable &p1, GLTools::SettableVariable &p2,
                                                unsigned long resolution1, unsigned long resolution2) {

    std::vector<glm::vec3> vertexs, normals, textcoords;
    vertexs.resize(resolution1 * resolution2);
    normals.resize(resolution1 * resolution2);
    textcoords.resize(resolution1 * resolution2);

    for (int i = 0; i < resolution1; i++) {
        for (int j = 0; j < resolution2; j++) {

            p1.set(1.0f * (float)i / (float)(resolution1 - 1));
            p2.set(1.0f * (float)j / (float)(resolution2 - 1));

            vertexs[i + j * resolution1] = glm::vec3(x.get(), y.get(), z.get());
            normals[i + j * resolution1] = glm::vec3(normX.get(), normY.get(), normZ.get());
            textcoords[i + j * resolution1] = glm::vec3(x.get(), y.get(), z.get());

        }
    }

    mSize = resolution1 * resolution2;

    mVertexArrayObject.add(VERTEX_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(vertexs)));
    mVertexArrayObject.add(NORMAL_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(normals)));
    mVertexArrayObject.add(TEXTCOORD_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(textcoords)));

}


void GLTools::ParametricDrawable::render(const GLTools::Camera &camera) const {
    mVertexArrayObject.bind();
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mSize));
    glBindVertexArray(0);
}
