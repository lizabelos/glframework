// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_TEXTURE_H
#define SOLAR_SYSTEM_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * Parse and create OpenGL texture
     */
    class Texture {

    public:
        Texture(const std::string &path);
        ~Texture();

        /**
         * You can't copy a texture, because the destructor call glDeleteTextures on a OpenGL pointer.
         */
        Texture( const Texture& ) = delete;
        Texture& operator=( const Texture& ) = delete;

        /**
         * Bind the texture on the given texture unit.
         * @param texture The texture unit on which the texture has to be bind.
         */
        void activate(GLenum texture);

    private:
        GLuint mId;


    };

}


#endif //SOLAR_SYSTEM_TEXTURE_H
