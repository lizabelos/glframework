//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_SHADER_H
#define SOLAR_SYSTEM_SHADER_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace GLTools {

    class Shader {

    public:
        Shader(GLenum type, const std::string &path);
        ~Shader();

        GLuint getId();

    private:
        GLuint mId;
        GLenum mType;

    };

}


#endif //SOLAR_SYSTEM_SHADER_H
