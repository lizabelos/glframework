//
// Created by thomas on 14/01/19.
//

#ifndef SOLAR_SYSTEM_TEXTUREMANAGER_H
#define SOLAR_SYSTEM_TEXTUREMANAGER_H

#include <memory>
#include <map>

#include "Texture.h"

namespace GLTools {

    class TextureManager {

    public:
        TextureManager(const std::string &path);

        std::shared_ptr<GLTools::Texture> operator[] (const std::string &name);

    private:
        std::string mPath;
        std::map<std::string, std::shared_ptr<GLTools::Texture>> mTextures;

    };

}


#endif //SOLAR_SYSTEM_TEXTUREMANAGER_H
