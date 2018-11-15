//
// Created by thomas on 15/11/18.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <iostream>
#include <stdexcept>

GLTools::Texture::Texture(const std::string &path) {

    std::cout << "Loading " << path << std::endl;

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 4);
    if(!data) {
        throw std::runtime_error("Can't open " + path);
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

}

GLTools::Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void GLTools::Texture::activate(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, mId);
}
