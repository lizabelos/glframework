#include "Window.h"

#include <stdexcept>
#include <iostream>

int sdlInitializationCount = 0;

GLTools::Window::Window(std::string name) {

    if (sdlInitializationCount == 0) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) throw std::runtime_error("SDL_INIT_VIDEO failed : '" + std::string(SDL_GetError()) + "'");
    }
    sdlInitializationCount++;

    mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
    if (!mWindow) throw std::runtime_error("SDL_CreateWindow failed : '" + std::string(SDL_GetError()) + "'");

    mContext = SDL_GL_CreateContext(mWindow);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw std::runtime_error(std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
    }
    else {
        std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    }

    if (!glewIsSupported("GL_VERSION_3_0")) {
        throw std::runtime_error("Error : GL Version 3.0 not supported ");
    }

}

GLTools::Window::~Window() {

    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);

    sdlInitializationCount--;
    if (sdlInitializationCount == 0) {
        SDL_Quit();
    }

}
