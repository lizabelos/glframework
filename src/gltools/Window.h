//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_GLWINDOW_H
#define SOLAR_SYSTEM_GLWINDOW_H


#include <string>
#include <list>
#include <memory>
#include <chrono>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Drawable"
#include "Camera"

namespace GLTools {

    class Window {

    public:
        explicit Window(const std::string &name);
        virtual ~Window();

        Window( const Window& ) = delete; // non construction-copyable
        Window& operator=( const Window& ) = delete; // non copyable

        int run();


    protected:
        glm::vec2 getMousePosition();
        float getTime();

        virtual void render(RenderStep renderStep) = 0;
        virtual void resize(unsigned int width, unsigned int height);
        virtual void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection);
        virtual void mouseMove(glm::vec2 mousePosition, unsigned int selection);
        virtual void keyboard(Uint32 type, Uint8 repeat, SDL_Keysym key);
        virtual void scroll(int x, int y);

    private:
        unsigned int processSelection(int x, int y);

        SDL_Window *mWindow;
        SDL_GLContext mContext;

        int mMouseX, mMouseY;

        std::chrono::steady_clock::time_point mBegin;

    };

}


#endif //SOLAR_SYSTEM_GLWINDOW_H
