#include <memory>

//
// Created by thomas on 11/14/18.
//

#include "ParametricDrawable.h"

void GLTools::ParametricDrawable::initialize(GLTools::Variable x, GLTools::Variable y,
                                                GLTools::Variable z, GLTools::Variable normX,
                                                GLTools::Variable normY, GLTools::Variable normZ,
                                                GLTools::Variable texX, GLTools::Variable texY,
                                                GLTools::SVariable p1, GLTools::SVariable p2,
                                                unsigned long resolution1, unsigned long resolution2) {

    mResolution1 = resolution1;
    mResolution2 = resolution2;

    std::vector<glm::vec3> vertexs, normals, textcoords;
    vertexs.resize(resolution1 * resolution2);
    normals.resize(resolution1 * resolution2);
    textcoords.resize(resolution1 * resolution2);

    for (int i = 0; i < resolution1; i++) {
        for (int j = 0; j < resolution2; j++) {

            p1->set(1.0f * (float)i / (float)(resolution1 - 1));
            p2->set(1.0f * (float)j / (float)(resolution2 - 1));

            vertexs[i + j * resolution1] = glm::vec3(x->get(), y->get(), z->get());
            normals[i + j * resolution1] = glm::vec3(normX->get(), normY->get(), normZ->get());
            textcoords[i + j * resolution1] = glm::vec3(texX->get(), texY->get(), 1);

        }
    }

    mSize = resolution1 * resolution2;

    mVertexArrayObject.add(VERTEX_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(vertexs)));
    mVertexArrayObject.add(NORMAL_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(normals)));
    mVertexArrayObject.add(TEXTCOORD_ID, std::shared_ptr<ArrayBuffer>(new ArrayBuffer(textcoords)));
    mVertexArrayObject.set(std::shared_ptr<ElementArrayBuffer>(new ElementArrayBuffer(getIndices(mResolution1, mResolution2))));
}


void GLTools::ParametricDrawable::render(const GLTools::Camera &camera) const {
    mVertexArrayObject.bind();
    glDrawElements(GL_TRIANGLES, getIndicesNumber(mResolution1, mResolution2), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mSize));
    glBindVertexArray(0);
}

std::vector<GLuint> GLTools::ParametricDrawable::getIndices(unsigned long resolution1, unsigned long resolution2) const {
    std::vector<GLuint> indices;
    indices.resize((resolution1 - 0) * (resolution2 - 0) * 6);

    unsigned long step1 = mResolution1 / resolution1;
    unsigned long step2 = mResolution2 / resolution2;

    for (int i = 0; i < resolution1 - 0; i = i + 1) {

        for (int j = 0; j < resolution2 - 0; j = j + 1) {

            unsigned long i0 = i * step1;
            unsigned long i1 = (i + 1) * step1;

            if (i0 > mResolution1 - 1) i0 = mResolution1 - 1;
            if (i1 > mResolution1 - 1) i1 = mResolution1 - 1;

            unsigned long j0 = j * step2;
            unsigned long j1 = (j + 1) * step2;

            if (j0 > mResolution2 - 1) j0 = mResolution2 - 1;
            if (j1 > mResolution2 - 1) j1 = mResolution2 - 1;

            indices[(i + j * (resolution1 - 0)) * 6 + 0] = static_cast<unsigned int>((i1) + (j1) * mResolution1);
            indices[(i + j * (resolution1 - 0)) * 6 + 1] = static_cast<unsigned int>((i1) + (j0) * mResolution1);
            indices[(i + j * (resolution1 - 0)) * 6 + 2] = static_cast<unsigned int>((i0) + (j1) * mResolution1);

            indices[(i + j * (resolution1 - 0)) * 6 + 3] = static_cast<unsigned int>((i0) + (j0) * mResolution1);
            indices[(i + j * (resolution1 - 0)) * 6 + 4] = static_cast<unsigned int>((i1) + (j0) * mResolution1);
            indices[(i + j * (resolution1 - 0)) * 6 + 5] = static_cast<unsigned int>((i0) + (j1) * mResolution1);

        }


    }

    return indices;
}

GLsizei GLTools::ParametricDrawable::getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const {
    return resolution1 * resolution2 * 6;
}