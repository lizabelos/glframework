//
// Created by thomas on 06/11/18.
//

#include "Drawable.h"

GLTools::Drawable::Drawable(unsigned int code) : mCode(code) {

}

unsigned int GLTools::Drawable::getCode() {
    return 0;
}

bool GLTools::Drawable::is(float codef) {
    unsigned int code = static_cast<unsigned int>(codef * 255.0f);
    return mCode == code;
}
