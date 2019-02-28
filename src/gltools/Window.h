// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_GLWINDOW_H
#define SOLAR_SYSTEM_GLWINDOW_H


#include <string>
#include <list>
#include <memory>
#include <chrono>
#include <set>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_sdl.h"
#include "../external/imgui/imgui_impl_opengl3.h"

#include "Drawable"
#include "Framebuffer"

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * Window is an abstract class which creates a window,and permits to render on it, and permits to handle his events
     * thanks to virtual function.
     */
    class Window {

    public:
        /**
         * Constructor for a Window with the given name.
         * @param name The title of the window.
         */
        explicit Window(const std::string &name);

        /**
         * The desctructor is virtual.
         */
        virtual ~Window();

        /**
         * You can't copy a window.
         */
        Window( const Window& ) = delete;
        Window& operator=( const Window& ) = delete;

        /**
         * Run a loop, which will :
         *  - Call the render function synchronized with the number of frame per seconds of the sreen
         *  - Call the protected events handlers functions
         * @return A main code.
         */
        int run();

    protected:
        /**
         * @return Return the relative position of the mouse between (-1,-1) and (1,1)
         * @see mouseMove
         * @see mouseClick
         */
        glm::vec2 getMousePosition();

        /**
         * @return Return the time since the window has been created in milliseconds.
         */
        float getTime();

        /**
         * A virtual function which has to render on the screen using OpenGL
         * @param renderStep The render step say if we render on the screen or on a buffer (like the selection buffer).
         * The shaders need to be adapted to the render type.
         */
        virtual void render(RenderStep renderStep) = 0;

        /**
         * A virtual function which is called when the window is resized
         * @param width The new width
         * @param height The new height
         */
        virtual void resize(unsigned int width, unsigned int height);

        /**
         * A virtual function which is called when a point on the window is clicked
         * @param mousePosition The relative position of the mouse between (-1,-1) and (1,1)
         * @param state SDL2 state of the mouse (release or pressed).
         * @param button The button which is pressed (left or right)
         * @param selection The value of the pixel in the selection buffer
         * @see getMousePosition
         * @see mouseMove
         */
        virtual void mouseClick(glm::vec2 mousePosition, Uint8 state, Uint8 button, unsigned int selection);

        /**
         * A virtual function which is called when the mouse move
         * @param mousePosition The relative position of the mouse between (-1,-1) and (1,1)
         * @param selection The value of the pixel in the selection buffer
         * @see getMousePosition
         * @see mouseClick
         */
        virtual void mouseMove(glm::vec2 mousePosition, unsigned int selection);

        /**
         * A virtual function which is called when scrolling (mouse scrolling or two fingers on touch screen)
         * @param x The x displacement
         * @param y The y displacement
         */
        virtual void scroll(int x, int y);

        /**
         * A virtual function which is called when the user key up or down
         * @param type Key up or down
         * @param repeat 0 if no repetition
         * @param key The SDL2 key id
         */
        virtual void keyboard(Uint32 type, bool repeat, int key);

        /**
         * A virtual function which if return true, wait for an event before rendering
         * @return true if need to wait for an event. Default false;
         */
        virtual bool waitEvent();

        /**
         * A virtual function which need to return true if we need a render
         * @return true if need a render
         */
        virtual bool needRender();

        /**
         * A virtual function which need to return true if we need a render of the shadow (only in deferred mode)
         * @return true if need a render
         */
        virtual bool needRenderShadow();

        /**
         * Enable or disable the deferred rendering
         * @param state true to enable or false to disable
         */
        void setDeferred(bool state);

        /**
         * Enable or disable the selection buffer
         * @param state true to enable or false to disable
         */
        void setSelectionBuffer(bool state);

        /**
         * Create a new ImGUI Frame
         */
        void newImguiFrame();

    private:
        void initGBuffer();
        void uninitGBuffer();

        void processEvent(const SDL_Event &event, bool &loop);
        unsigned int processSelection(int x, int y);

        SDL_Window *mWindow;
        SDL_GLContext mContext;

        int mMouseX, mMouseY;

        std::chrono::steady_clock::time_point mBegin;
        std::set<int> mPressedKey;

        std::shared_ptr<Framebuffer> mFramebuffer;
        std::shared_ptr<ShadowFramebuffer> mShadowFramebuffer;

        bool mSelectionBuffer = false, mDeferred = false;

    };

}


#endif //SOLAR_SYSTEM_GLWINDOW_H
