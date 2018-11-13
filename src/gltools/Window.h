//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_GLWINDOW_H
#define SOLAR_SYSTEM_GLWINDOW_H


#include <string>
#include <list>
#include <memory>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Drawable"
#include "Camera"

namespace GLTools {

    class Window {

    public:
        explicit Window(std::string name);
        virtual ~Window();

        Window( const Window& ) = delete; // non construction-copyable
        Window& operator=( const Window& ) = delete; // non copyable

        int run();


    protected:
        void init();
        virtual void render() = 0;

    private:
        SDL_Window *mWindow;
        SDL_GLContext mContext;

    };

}


#endif //SOLAR_SYSTEM_GLWINDOW_H
