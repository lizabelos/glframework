//
// Created by thomas on 06/11/18.
//

#include "Drawable.h"

template<typename vecType> GLTools::Drawable<vecType>::Drawable(unsigned int code) : mCode(code) {
    mCode = code;
}

template<typename vecType> unsigned int GLTools::Drawable<vecType>::getCode() {
    return mCode;
}

template<typename vecType> bool GLTools::Drawable<vecType>::is(float codef) {
    unsigned int code = static_cast<unsigned int>(codef * 255.0f);
    return mCode == code;
}

template<typename vecType> GLTools::TransformDrawable<vecType>::TransformDrawable(std::shared_ptr<GLTools::Drawable<vecType>> drawable) : GLTools::Drawable<vecType>(0), mDrawable(drawable), mRotation(0.0f), mScale(1.0f), mTranslation(0.0f) {

}

template<typename vecType> void GLTools::TransformDrawable<vecType>::render(ModelView <vecType> &camera,
                                                                             std::shared_ptr<GLTools::Program> program,
                                                                             GLTools::RenderStep renderStep) const {
    camera.pushMatrix();
    camera.translate(mTranslation);
    camera.rotate(mRotation, mRotationAxis);
    camera.scale(mScale);
    mDrawable->render(camera, program, renderStep);
    camera.popMatrix();
}

template<typename vecType> unsigned int GLTools::TransformDrawable<vecType>::getCode() {
    return mDrawable->getCode();
}

template<typename vecType> bool GLTools::TransformDrawable<vecType>::is(float code) {
    return mDrawable->is(code);
}

template<typename vecType> void GLTools::TransformDrawable<vecType>::move(vecType translation) {
    mTranslation += translation;
}

template<typename vecType>
void GLTools::TransformDrawable<vecType>::scale(vecType scale) {
    mScale *= scale;
}

template<typename vecType>
void GLTools::TransformDrawable<vecType>::rotate(float rotation, vecType rotationAxis) {
    mRotation += rotation;
    mRotationAxis = rotationAxis; // todo : false
}

template<typename vecType>
vecType GLTools::TransformDrawable<vecType>::getTranslation() {
    return mTranslation;
}

template<typename vecType>
void GLTools::TransformDrawable<vecType>::setTranslation(vecType translation) {
    mTranslation = translation;
}

template<typename vecType>
vecType GLTools::TransformDrawable<vecType>::getScale() {
    return mScale;
}
