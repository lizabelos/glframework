//
// Created by belos on 26/02/2019.
//

#include "Model.h"

GLTools::Model2D::Model2D() {
    mModelMatrix = glm::mat3(1.0f);
}

glm::mat3 GLTools::Model2D::getMatrix() const {
    return mModelMatrix;
}

void GLTools::Model2D::pushMatrix() {
    mMVMatrixStack.push_back(mModelMatrix);
}

void GLTools::Model2D::popMatrix() {
    mModelMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::Model2D::translate(glm::vec2 t) {
    glm::mat3 translationMatrix = {
            1  , 0  , 0,
            0  , 1  , 0,
            t.x, t.y, 1
    };
    mModelMatrix = mModelMatrix * translationMatrix;
}

void GLTools::Model2D::rotate(float angle) {
    glm::mat3 rotationMatrix = {
            cosf(angle) , sinf(angle), 0,
            -sinf(angle), cosf(angle), 0,
            0           , 0          , 1
    };
    mModelMatrix = mModelMatrix * rotationMatrix;
}

void GLTools::Model2D::scale(glm::vec2 s) {
    glm::mat3 scaleMatrix = {
            s.x, 0  , 0,
            0  , s.y, 0,
            0  , 0  , 1
    };
    mModelMatrix = mModelMatrix * scaleMatrix;
}

void GLTools::Model2D::scale(float scaling) {
    return scale(glm::vec2(scaling, scaling));
}

void GLTools::Model2D::identity() {
    mModelMatrix = glm::mat4(1.0f);
}

GLTools::Model3D::Model3D() {
    mModelMatrix = glm::mat4(1.0f);
}

glm::mat4 GLTools::Model3D::getMatrix() const {
    return mModelMatrix;
}

void GLTools::Model3D::pushMatrix() {
    mMVMatrixStack.push_back(mModelMatrix);
}

void GLTools::Model3D::popMatrix() {
    mModelMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::Model3D::translate(glm::vec3 translation) {
    mModelMatrix = glm::translate(mModelMatrix, translation);
}

void GLTools::Model3D::rotate(float angle, glm::vec3 axis) {
    mModelMatrix = glm::rotate(mModelMatrix, angle, axis);
}

void GLTools::Model3D::scale(glm::vec3 scaling) {
    mModelMatrix = glm::scale(mModelMatrix, scaling);
}

void GLTools::Model3D::scale(float scaling) {
    mModelMatrix = glm::scale(mModelMatrix, glm::vec3(scaling, scaling, scaling));
}

void GLTools::Model3D::identity() {
    mModelMatrix = glm::mat4(1.0f);
}