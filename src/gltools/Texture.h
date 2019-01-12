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

    /**
     * Parse and create OpenGL cube texture
     */
    class TextureCubeMap {

    public:
        TextureCubeMap(const std::string &xpos, const std::string &xneg, const std::string &ypos, const std::string &yneg, const std::string &zpos, const std::string &zneg);
        ~TextureCubeMap();

        /**
         * You can't copy a texture, because the destructor call glDeleteTextures on a OpenGL pointer.
         */
        TextureCubeMap( const Texture& ) = delete;
        TextureCubeMap& operator=( const Texture& ) = delete;

        /**
         * Bind the texture on the given texture unit.
         * @param texture The texture unit on which the texture has to be bind.
         */
        void activate(GLenum texture);

    private:
        void setup(GLenum target, const std::string &path);

        GLuint mId;

    };

}


#endif //SOLAR_SYSTEM_TEXTURE_H
