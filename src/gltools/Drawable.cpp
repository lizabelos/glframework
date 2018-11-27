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

template<typename vecType> GLTools::TranslatedDrawable<vecType>::TranslatedDrawable(std::shared_ptr<GLTools::Drawable<vecType>> drawable, vecType translation) : GLTools::Drawable<vecType>(0), mDrawable(drawable), mTranslation(translation) {

}

template<typename vecType> void GLTools::TranslatedDrawable<vecType>::render(Camera <vecType> &camera,
                                                                             std::shared_ptr<GLTools::Program> program,
                                                                             GLTools::RenderStep renderStep) const {
    camera.pushMatrix();
    camera.translate(mTranslation);
    mDrawable->render(camera, program, renderStep);
    camera.popMatrix();
}

template<typename vecType> unsigned int GLTools::TranslatedDrawable<vecType>::getCode() {
    return mDrawable->getCode();
}

template<typename vecType> bool GLTools::TranslatedDrawable<vecType>::is(float code) {
    return mDrawable->is(code);
}

template<typename vecType> void GLTools::TranslatedDrawable<vecType>::move(vecType translation) {
    mTranslation += translation;
}
