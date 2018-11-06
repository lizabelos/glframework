#include "Window.h"

#include <stdexcept>
#include <iostream>

int sdlInitializationCount = 0;

void glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

    std::cerr << "GL CALLBACK: " << message << std::endl;

    if (type == GL_DEBUG_TYPE_ERROR) {
        throw std::runtime_error(message);
    }

}


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

    // For compatibility with old graphics cards, we use OpenGL 3.0 with experimental functions.
    if (!glewIsSupported("GL_VERSION_3_0")) {
        throw std::runtime_error("Error : GL Version 3.0 not supported ");
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)glMessageCallback, nullptr);

}

GLTools::Window::~Window() {

    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);

    sdlInitializationCount--;
    if (sdlInitializationCount == 0) {
        SDL_Quit();
    }

}

void GLTools::Window::add(std::shared_ptr<Drawable> pDrawable) {
    switch (pDrawable->step()) {
        case Step2D:
            mDrawables2D.push_back(pDrawable);
            break;
        case Step3D:
            mDrawables3D.push_back(pDrawable);
            break;
    }
}

void GLTools::Window::init() {

    glClearColor(0.0f, 0.6f, 0.9f, 0.0f);
    glClearDepth(1.0f);

    // Depth Test
    glEnable(GL_DEPTH_TEST);

    // Enable Alpha Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable multisampling
    glEnable(GL_MULTISAMPLE_ARB);

    mProjectionMatrix = glm::perspective(glm::radians(70.f), (float)(800.0 / 600.0), 0.1f, 100.0f);

}


void GLTools::Window::render() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // todo : camera matrix

    for (const std::shared_ptr<Drawable> &drawable : mDrawables3D) {
        drawable->render();
    }

    // todo : 2d matrix

    for (const std::shared_ptr<Drawable> &drawable : mDrawables2D) {
        drawable->render();
    }

    SDL_GL_SwapWindow(mWindow);

}

int GLTools::Window::run() {

    init();

    bool loop = true;

    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                loop = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    default:
                        break;
                }
            }
        }

        render();

    }

    return 0;
}
