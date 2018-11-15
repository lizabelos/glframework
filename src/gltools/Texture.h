//
// Created by thomas on 15/11/18.
//

#ifndef SOLAR_SYSTEM_TEXTURE_H
#define SOLAR_SYSTEM_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace GLTools {

    class Texture {

    public:
        Texture(const std::string &path);
        ~Texture();

        void activate(GLenum texture);

    private:
        GLuint mId;


    };

}


#endif //SOLAR_SYSTEM_TEXTURE_H
