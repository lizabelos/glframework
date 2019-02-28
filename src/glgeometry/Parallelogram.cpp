//
// Created by thomas on 26/12/18.
//

#include "Parallelogram.h"

// todo
GLfloat cube_vertices[] = {
        -1.0,  1.0,  1.0,
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
};

GLushort cube_indices[] = {
        0, 1, 2, 3,
        3, 2, 6, 7,
        7, 6, 5, 4,
        4, 5, 1, 0,
        0, 3, 7, 4,
        1, 2, 6, 5,
};

GLGeometry::Parallelogram::Parallelogram(unsigned int code) : Drawable(code) {

    std::vector<glm::vec3> vertexs;
    std::vector<GLuint> indices;
    for (int i = 0; i < sizeof(cube_vertices); i = i + 3) {
        vertexs.emplace_back(glm::vec3(cube_vertices[i], cube_vertices[i + 1], cube_vertices[i + 2]));
    }

    for (int i = 0; i < sizeof(cube_indices); i++) {
        indices.emplace_back(cube_indices[i]);
    }

    mSize = indices.size();


    mVertexArrayObject.add(VERTEX_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
    mVertexArrayObject.add(NORMAL_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
    mVertexArrayObject.add(TEXTCOORD_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
    mVertexArrayObject.set(std::make_shared<GLTools::ElementArrayBuffer>(indices));

}

void GLGeometry::Parallelogram::render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const {

    program->use();

    mVertexArrayObject.bind();
    glDrawElements(GL_QUADS, mSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

