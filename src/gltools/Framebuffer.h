// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef BELOSGL_FRAMEBUFFER_H
#define BELOSGL_FRAMEBUFFER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/ext.hpp>

namespace GLTools {

    typedef enum GBufferTextureType
    {
        GPosition = 0,
        GNormal,
        GAmbient,
        GDiffuse,
        GGlossyShininess,
        GDepth, // On doit créer une texture de depth mais on écrit pas directement dedans dans le FS. OpenGL le fait pour nous (et l'utilise).
        GBufferTextureCount
    } GBufferTextureType;

    // Warning : GL_RGB32F is unsupported of a lot of computer. Using GL_RGBA32F instead.
    const GLenum GBufferTextureFormat[GBufferTextureCount] = { GL_RGBA32F, GL_RGBA32F, GL_RGBA32F, GL_RGBA32F, GL_RGBA32F, GL_DEPTH_COMPONENT32F };

    const GLenum GDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
    const int GDrawBuffersSize = 5;

    class Framebuffer {

    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        void use();
        void bindTextures();

        static void useScreen();

        /**
         * You can't copy a Framebuffer.
         */
        Framebuffer( const Framebuffer& ) = delete;
        Framebuffer& operator=( const Framebuffer& ) = delete;

    private:
        GLuint mGBufferTextures[GBufferTextureCount];
        GLuint mFBO;

    };

    class ShadowFramebuffer {

    public:
        ShadowFramebuffer();
        ~ShadowFramebuffer();

        void use();
        void bindTexture();

        /**
         * You can't copy a Framebuffer.
         */
        ShadowFramebuffer( const Framebuffer& ) = delete;
        ShadowFramebuffer& operator=( const Framebuffer& ) = delete;

    private:
        GLuint mDirectionalSMCubemap;
        GLuint mDirectionalSMFBO;
        GLuint mDirectionalSMSampler;
        int mDirectionalSMResolution = 1024;

    };

}


#endif //BELOSGL_FRAMEBUFFER_H
