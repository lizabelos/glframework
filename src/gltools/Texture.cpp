//
// Created by thomas on 15/11/18.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

#include <iostream>
#include <stdexcept>

GLTools::Texture::Texture(const std::string &path) {

    glDisable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_TEXTURE_2D);

    std::cout << "Loading " << path << std::endl;

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 4);
    if(!data) {
        data = stbi_load((path + ".jpg").c_str(), &x, &y, &n, 4);
        if(!data) {
            throw std::runtime_error("Can't open " + path);
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_CUBE_MAP);
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
    glDisable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, mId);
}

GLTools::TextureCubeMap::TextureCubeMap(const std::string &xpos, const std::string &xneg, const std::string &ypos, const std::string &yneg, const std::string &zpos, const std::string &zneg) {

    std::cout << "Loading texture cube map : " << std::endl;

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);


    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    setup(GL_TEXTURE_CUBE_MAP_POSITIVE_X, xpos);
    setup(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, xneg);
    setup(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, ypos);
    setup(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, yneg);
    setup(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, zpos);
    setup(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, zneg);


}

GLTools::TextureCubeMap::~TextureCubeMap() {
    glDeleteTextures(1, &mId);
}

void GLTools::TextureCubeMap::activate(GLenum texture) {

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);

    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);
}

void GLTools::TextureCubeMap::setup(GLenum target, const std::string &path) {

    std::cout << " - Texture map " << path << std::endl;

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 4);
    if(!data) {
        throw std::runtime_error("Can't open " + path);
    }

    glTexImage2D(target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
