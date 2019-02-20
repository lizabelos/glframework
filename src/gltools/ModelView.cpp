//
// Created by thomas on 06/11/18.
//

#include "ModelView.h"

template<typename vecType> vecType GLTools::ModelView<vecType>::getPosition() {
    return vecType(0.0f);
}

GLTools::ModelView3D::ModelView3D() {
    resize(1,1);
    mMVMatrix = glm::mat4(1.0f);
    mFar = 1000.0f;
    mNear = 0.1f;
}

GLTools::ModelView3D::ModelView3D(unsigned int width, unsigned int height) {
    resize(width, height);
    mMVMatrix = glm::mat4(1.0f);
    mFar = 1000.0f;
    mNear = 0.1f;
}

void GLTools::ModelView3D::resize(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)width / (float)height, mNear, mFar);
}

void GLTools::ModelView3D::setPerspective(float far, float near) {
    mFar = far;
    mNear = near;
    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)mWidth / (float)mHeight, mNear, mFar);
}

glm::mat4 GLTools::ModelView3D::getProjectionMatrix() const {
    return mProjectionMatrix;
}

glm::mat4 GLTools::ModelView3D::getModelMatrix() const {
    return mMVMatrix;
}

glm::mat4 GLTools::ModelView3D::getViewMatrix() const {
    return glm::mat4(1.0f);
}

glm::mat4 GLTools::ModelView3D::getMVMatrix() const {
    return getViewMatrix() * getModelMatrix();
}

glm::mat4 GLTools::ModelView3D::getNormalMatrix() const {
    return glm::transpose(glm::inverse(getMVMatrix()));
}

void GLTools::ModelView3D::pushMatrix() {
    mMVMatrixStack.push_back(mMVMatrix);
}

void GLTools::ModelView3D::popMatrix() {
    mMVMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::ModelView3D::translate(glm::vec3 translation) {
    mMVMatrix = glm::translate(mMVMatrix, translation);
}

void GLTools::ModelView3D::rotate(float angle, glm::vec3 axis) {
    mMVMatrix = glm::rotate(mMVMatrix, angle, axis);
}


void GLTools::ModelView3D::scale(glm::vec3 scaling) {
    mMVMatrix = glm::scale(mMVMatrix, scaling);
}

void GLTools::ModelView3D::scale(float scaling) {
    mMVMatrix = glm::scale(mMVMatrix, glm::vec3(scaling, scaling, scaling));
}

void GLTools::ModelView3D::identity() {
    mMVMatrix = glm::mat4(1.0f);
}

void GLTools::ModelView3D::enableTranslation() {

}

void GLTools::ModelView3D::disableTranslation() {

}


GLTools::ModelView2D::ModelView2D() {
    resize(1,1);
    mMVMatrix = glm::mat3(1.0f);
}

GLTools::ModelView2D::ModelView2D(unsigned int width, unsigned int height) {
    resize(width, height);
    mMVMatrix = glm::mat3(1.0f);
}

void GLTools::ModelView2D::resize(unsigned int width, unsigned int height) {
    mProjectionMatrix = glm::mat3(1.0f);
    unsigned int min = width;
    if (height < min) min = height;
    mWindowSize = glm::vec2(width, height) / (float)min;
}

glm::mat4 GLTools::ModelView2D::getProjectionMatrix() const {
    return glm::mat4(mProjectionMatrix);
}

glm::mat4 GLTools::ModelView2D::getMVMatrix() const {
    return getViewMatrix() * getModelMatrix();
}

glm::mat4 GLTools::ModelView2D::getModelMatrix() const {
    /*glm::mat3 scaleMatrix = {
            1 / mWindowSize.x, 0  , 0,
            0  , 1 / mWindowSize.y, 0,
            0  , 0  , 1
    };*/
    //return glm::mat4(scaleMatrix * mMVMatrix);
    return glm::mat4(mMVMatrix);
}

glm::mat4 GLTools::ModelView2D::getViewMatrix() const {
    return glm::mat4(1.0f);
}

glm::mat4 GLTools::ModelView2D::getNormalMatrix() const {
    return glm::mat4(glm::transpose(glm::inverse(getMVMatrix())));
}

void GLTools::ModelView2D::pushMatrix() {
    mMVMatrixStack.push_back(mMVMatrix);
}

void GLTools::ModelView2D::popMatrix() {
    mMVMatrix = mMVMatrixStack.back();
    mMVMatrixStack.pop_back();
}

void GLTools::ModelView2D::translate(glm::vec2 t) {
    glm::mat3 translationMatrix = {
            1  , 0  , 0,
            0  , 1  , 0,
            t.x, t.y, 1
    };
    mMVMatrix = mMVMatrix * translationMatrix;
}

void GLTools::ModelView2D::rotate(float angle, glm::vec2 axis) {
    glm::mat3 rotationMatrix = {
            cosf(angle) , sinf(angle), 0,
            -sinf(angle), cosf(angle), 0,
            0           , 0          , 1
    };
    mMVMatrix = mMVMatrix * rotationMatrix;
}


void GLTools::ModelView2D::scale(glm::vec2 s) {
    glm::mat3 scaleMatrix = {
            s.x, 0  , 0,
            0  , s.y, 0,
            0  , 0  , 1
    };
    mMVMatrix = mMVMatrix * scaleMatrix;
}

void GLTools::ModelView2D::scale(float scaling) {
    return scale(glm::vec2(scaling, scaling));
}

void GLTools::ModelView2D::identity() {
    mMVMatrix = glm::mat3(1.0f);
}

