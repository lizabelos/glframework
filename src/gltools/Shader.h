// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_SHADER_H
#define SOLAR_SYSTEM_SHADER_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * Parse and create OpenGL vertex and fragment shader.
     */
    class Shader {

    public:
        /**
         * Create and compile and shader
         * @param type The kind of shader (fragment or vertex)
         * @param path The path of the source code of the shader
         */
        Shader(GLenum type, const std::string &path);
        ~Shader();

        /**
         * You can't copy a shader, because the destructor call glDeleteShader on a OpenGL pointer.
         */
        Shader( const Shader& ) = delete;
        Shader& operator=( const Shader& ) = delete;

        /**
         * Return the OpenGL pointer to the shader.
         * @return
         */
        GLuint getId();

    private:
        GLuint mId;
        GLenum mType;

    };

}


#endif //SOLAR_SYSTEM_SHADER_H
