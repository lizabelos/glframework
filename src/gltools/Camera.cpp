//
// Created by thomas on 06/11/18.
//

#include "Camera.h"

template<typename vecType> glm::mat4 GLTools::Camera<vecType>::getModelMatrix() const {
    return getMVMatrix();
}

template<typename vecType> vecType GLTools::Camera<vecType>::getPosition() {
    return vecType(0.0f);
}

GLTools::Camera3D::Camera3D() {
    resize(1,1);
    mMVMatrix = glm::mat4(1.0f);
    mFar = 1000.0f;
    mNear = 0.1f;
}

GLTools::Camera3D::Camera3D(unsigned int width, unsigned int height) {
    resize(width, height);
    mMVMatrix = glm::mat4(1.0f);
    mFar = 1000.0f;
    mNear = 0.1f;
}

void GLTools::Camera3D::resize(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)width / (float)height, mNear, mFar);
}

void GLTools::Camera3D::setPerspective(float far, float near) {
    mFar = far;
    mNear = near;
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)mWidth / (float)mHeight, mNear, mFar);
}

glm::mat4 GLTools::Camera3D::getProjectionMatrix() const {
    return mProjectionMatrix;
}

glm::mat4 GLTools::Camera3D::getMVMatrix() const {
    return mMVMatrix;
}

glm::mat4 GLTools::Camera3D::getNormalMatrix() const {
    return glm::transpose(glm::inverse(mMVMatrix));
}

void GLTools::Camera3D::pushMatrix() {
    mMVMatrixStack.push_back(mMVMatrix);
}

void GLTools::Camera3D::popMatrix() {
    mMVMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::Camera3D::translate(glm::vec3 translation) {
    mMVMatrix = glm::translate(mMVMatrix, translation);
}

void GLTools::Camera3D::rotate(float angle, glm::vec3 axis) {
    mMVMatrix = glm::rotate(mMVMatrix, angle, axis);
}


void GLTools::Camera3D::scale(glm::vec3 scaling) {
    mMVMatrix = glm::scale(mMVMatrix, scaling);
}

void GLTools::Camera3D::scale(float scaling) {
    mMVMatrix = glm::scale(mMVMatrix, glm::vec3(scaling, scaling, scaling));
}

void GLTools::Camera3D::identity() {
    mMVMatrix = glm::mat4(1.0f);
}

void GLTools::Camera3D::enableTranslation() {

}

void GLTools::Camera3D::disableTranslation() {

}


GLTools::Camera2D::Camera2D() {
    resize(1,1);
    mMVMatrix = glm::mat3(1.0f);
}

GLTools::Camera2D::Camera2D(unsigned int width, unsigned int height) {
    resize(width, height);
    mMVMatrix = glm::mat3(1.0f);
}

void GLTools::Camera2D::resize(unsigned int width, unsigned int height) {
    mProjectionMatrix = glm::mat3(1.0f);
    unsigned int min = width;
    if (height < min) min = height;
    mWindowSize = glm::vec2(width, height) / (float)min;
}

glm::mat4 GLTools::Camera2D::getProjectionMatrix() const {
    return glm::mat4(mProjectionMatrix);
}

glm::mat4 GLTools::Camera2D::getMVMatrix() const {
    glm::mat3 scaleMatrix = {
            1 / mWindowSize.x, 0  , 0,
            0  , 1 / mWindowSize.y, 0,
            0  , 0  , 1
    };
    return glm::mat4(scaleMatrix * mMVMatrix);
}

glm::mat4 GLTools::Camera2D::getNormalMatrix() const {
    return glm::mat4(glm::transpose(glm::inverse(getMVMatrix())));
}

void GLTools::Camera2D::pushMatrix() {
    mMVMatrixStack.push_back(mMVMatrix);
}

void GLTools::Camera2D::popMatrix() {
    mMVMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::Camera2D::translate(glm::vec2 t) {
    glm::mat3 translationMatrix = {
            1  , 0  , 0,
            0  , 1  , 0,
            t.x, t.y, 1
    };
    mMVMatrix = mMVMatrix * translationMatrix;
}

void GLTools::Camera2D::rotate(float angle, glm::vec2 axis) {
    glm::mat3 rotationMatrix = {
            cosf(angle) , sinf(angle), 0,
            -sinf(angle), cosf(angle), 0,
            0           , 0          , 1
    };
    mMVMatrix = mMVMatrix * rotationMatrix;
}


void GLTools::Camera2D::scale(glm::vec2 s) {
    glm::mat3 scaleMatrix = {
            s.x, 0  , 0,
            0  , s.y, 0,
            0  , 0  , 1
    };
    mMVMatrix = mMVMatrix * scaleMatrix;
}

void GLTools::Camera2D::scale(float scaling) {
    return scale(glm::vec2(scaling, scaling));
}

void GLTools::Camera2D::identity() {
    mMVMatrix = glm::mat3(1.0f);
}

