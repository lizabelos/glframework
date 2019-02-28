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

