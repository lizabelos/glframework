#include "Framebuffer.h"

GLTools::Framebuffer::Framebuffer(int width, int height) {

    std::cout << "Creating frame buffer object of size " << width << "x" << height << "..." << std::endl;

    for (int i = 0; i < GBufferTextureCount; i++) {
        std::cout << "Creating texture " << i << std::endl;
        glGenTextures(1, &mGBufferTextures[i]);
        glBindTexture(GL_TEXTURE_2D, mGBufferTextures[i]);
        glTexStorage2D(GL_TEXTURE_2D, 1, GBufferTextureFormat[i], width, height);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::cout << "Generating framebuffer..." << std::endl;
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFBO);

    for (int i = 0; i < GBufferTextureCount; i++) {

        if ((GBufferTextureType)i == GDepth) {
            std::cout << "Creating Depth Attachment..." << std::endl;
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mGBufferTextures[i], 0);
        } else {
            std::cout << "Creating Color Attachment " << i << " ..." << std::endl;
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mGBufferTextures[i], 0);
        }

    }

    glDrawBuffers(GDrawBuffersSize, GDrawBuffers);

    GLenum framebufferStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    switch (framebufferStatus) {
        case GL_FRAMEBUFFER_COMPLETE:
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:  throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
        case GL_FRAMEBUFFER_UNSUPPORTED: throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_UNSUPPORTED");
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: throw std::runtime_error("gl draw framebuffer is not complete. GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
        default:
            throw std::runtime_error("gl draw framebuffer is not complete. unknown error :(");

    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

}

GLTools::Framebuffer::~Framebuffer() {

    glDeleteFramebuffers(1, &mFBO);

    for (int i = 0; i < GBufferTextureCount; i++) {
        glDeleteTextures(1, &mGBufferTextures[i]);
    }

}

void GLTools::Framebuffer::use() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFBO);
    glDrawBuffers(GDrawBuffersSize, GDrawBuffers);
}

void GLTools::Framebuffer::useScreen() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GLTools::Framebuffer::bindTextures() {
    for (int i = 0; i < GDrawBuffersSize; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mGBufferTextures[i]);
    }
}