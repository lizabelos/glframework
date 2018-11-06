//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_GLWINDOW_H
#define SOLAR_SYSTEM_GLWINDOW_H


#include <string>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace GLTools {

    class Window {

    public:
        explicit Window(std::string name);
        ~Window();

    private:
        SDL_Window *mWindow;
        SDL_GLContext mContext;

    };

}


#endif //SOLAR_SYSTEM_GLWINDOW_H
