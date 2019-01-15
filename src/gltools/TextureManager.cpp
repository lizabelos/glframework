//
// Created by thomas on 14/01/19.
//

#include "TextureManager.h"

GLTools::TextureManager::TextureManager(const std::string &path) : mPath(path) {

}

std::shared_ptr<GLTools::Texture> GLTools::TextureManager::operator[](const std::string &name) {
    if (mTextures.count(name) == 0) {
        mTextures[name] = std::make_shared<GLTools::Texture>(mPath + "/" + name);
    }
    return mTextures[name];
}
