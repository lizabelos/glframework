#include "Window.h"

#include <stdexcept>
#include <iostream>

// int sdlInitializationCount = 0;

void glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

    std::cerr << "GL CALLBACK: " << message << std::endl;

    if (type == GL_DEBUG_TYPE_ERROR) {
        throw std::runtime_error(message);
    }

}


GLTools::Window::Window(const std::string &name) : mMouseX(0), mMouseY(0) {

    mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    if (!mWindow) throw std::runtime_error("SDL_CreateWindow failed : '" + std::string(SDL_GetError()) + "'");

    SDL_SetWindowResizable(mWindow, SDL_TRUE);

    mContext = SDL_GL_CreateContext(mWindow);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw std::runtime_error(std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
    }
    else {
        std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)glMessageCallback, nullptr);

}

GLTools::Window::~Window() {
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);

}

int GLTools::Window::run() {

    mBegin = std::chrono::steady_clock::now();

    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);
    resize(w, h);

    bool loop = true;

    while (loop) {

        if (mSelectionBuffer) {

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Depth Test
            glEnable(GL_DEPTH_TEST);

            // Disable Alpha Blending
            glDisable(GL_BLEND);

            render(RENDER_SELECTION);

        }

        do {
            SDL_Event event;
            if (waitEvent()) {
                SDL_WaitEvent(&event);
                processEvent(event, loop);
            }

            for (int key : mPressedKey) {
                keyboard(SDL_KEYDOWN, true, key);
            }

            while (SDL_PollEvent(&event)) {
                processEvent(event, loop);
            }

        } while (!needRender() && loop);

        SDL_GetWindowSize(mWindow, &w, &h);

        if (!mDeferred) {

            glViewport(0, 0, w, h);

            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Depth Test
            glEnable(GL_DEPTH_TEST);

            // Enable Alpha Blending
            // glEnable(GL_BLEND);
            // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            render(RENDER_SCREEN);
            SDL_GL_SwapWindow(mWindow);

        } else {

            // Depth Test
            glEnable(GL_DEPTH_TEST);

            if (needRenderShadow()) {

                mShadowFramebuffer->use();
                glClear(GL_DEPTH_BUFFER_BIT);
                render(RENDER_DEFERRED_SHADOW);

            }

            mFramebuffer->use();
            glViewport(0, 0, w, h);

            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            render(RENDER_DEFERRED_FRAMEBUFFER);

            mFramebuffer->useScreen();
            glViewport(0, 0, w, h);

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mFramebuffer->bindTextures();
            mShadowFramebuffer->bindTexture();

            render(RENDER_DEFERRED_SCREEN);

            SDL_GL_SwapWindow(mWindow);

        }

    }

    return 0;
}

glm::vec2 GLTools::Window::getMousePosition() {
    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);

    int min = w;
    if (h < min) min = h;

    return glm::vec2((float)mMouseX / (float)min, (float)mMouseY / (float)min);
}

float GLTools::Window::getTime() {
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    float currentTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(end - mBegin).count() * 1e-6f;
    return currentTime;
}

unsigned int GLTools::Window::processSelection(int x, int y) {
    float res[4];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_FLOAT, &res);

    return static_cast<unsigned int>(res[0] * 255.0);
}


void GLTools::Window::resize(unsigned int width, unsigned int height) {

}

void GLTools::Window::mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection) {

}

void GLTools::Window::scroll(int x, int y) {

}

void GLTools::Window::mouseMove(glm::vec2 mousePosition, unsigned int selection) {

}

void GLTools::Window::keyboard(Uint32 type, bool repeat, int key) {

}

void GLTools::Window::processEvent(const SDL_Event &event, bool &loop) {
    if (event.type == SDL_QUIT) {
        loop = false;
    }
    if (event.type == SDL_KEYDOWN)
    {
        if (mPressedKey.count(event.key.keysym.sym) == 0) {
            mPressedKey.insert(event.key.keysym.sym);
            keyboard(SDL_KEYDOWN, false, event.key.keysym.sym);
        }
    }
    if (event.type == SDL_KEYUP) {
        mPressedKey.erase(event.key.keysym.sym);
        keyboard(SDL_KEYUP, false, event.key.keysym.sym);
    }
    if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                // glViewport(0, 0, event.window.data1, event.window.data2);
                if (mDeferred) mFramebuffer = std::make_shared<Framebuffer>(event.window.data1, event.window.data2);
                resize(static_cast<unsigned int>(event.window.data1), static_cast<unsigned int>(event.window.data2));
                break;
            default:
                break;
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mMouseX, &mMouseY);
        unsigned int selection = processSelection(mMouseX, mMouseY);
        mouseMove(getMousePosition(), selection);
    }
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&mMouseX, &mMouseY);
        unsigned int selection = processSelection(mMouseX, mMouseY);
        mouseClick(getMousePosition(), event.button.state, event.button.button, selection);
    }
    if (event.type == SDL_MOUSEWHEEL) {
        scroll(event.wheel.x, event.wheel.y);
    }
}

bool GLTools::Window::waitEvent() {
    return false;
}

bool GLTools::Window::needRender() {
    return true;
}

bool GLTools::Window::needRenderShadow() {
    return false;
}

void GLTools::Window::setDeferred(bool state) {
    mDeferred = state;
    if (mDeferred) {
        int w, h;
        SDL_GetWindowSize(mWindow, &w, &h);
        mFramebuffer = std::make_shared<Framebuffer>(w, h);
        mShadowFramebuffer = std::make_shared<ShadowFramebuffer>();
    } else {
        mFramebuffer = std::shared_ptr<Framebuffer>(nullptr);
        mShadowFramebuffer = std::shared_ptr<ShadowFramebuffer>(nullptr);
    }
}

void GLTools::Window::setSelectionBuffer(bool state) {
    mSelectionBuffer = state;
}
