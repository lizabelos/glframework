//
// Created by thomas on 11/26/18.
//

#include "Triangle.h"

GLGeometry::Triangle::Triangle(unsigned int code) : GLTools::Drawable(code) {

    std::vector<glm::vec3> vertexs;
    vertexs.emplace_back(glm::vec3(0, 1, 0));
    vertexs.emplace_back(glm::vec3(1, -1, 0));
    vertexs.emplace_back(glm::vec3(-1, -1, 0));

    std::vector<GLuint> indices;
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(2);


    mVertexArrayObject.add(VERTEX_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
    mVertexArrayObject.add(NORMAL_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
    mVertexArrayObject.add(TEXTCOORD_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));

}

void GLGeometry::Triangle::render(const GLTools::Camera &camera, GLTools::RenderStep renderStep) const {
    mVertexArrayObject.bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
