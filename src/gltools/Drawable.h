// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_DRAWABLE_H
#define SOLAR_SYSTEM_DRAWABLE_H

#include <vector>
#include <memory>

#include "Program"

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * Different kind of rendering.
     */
    typedef enum RenderStep {
        /**
         * Render directly on the screen.
         */
        RENDER_SCREEN,
        /**
         * Render on a selection buffer.
         */
        RENDER_SELECTION,
        /**
         * Deferred render on the framebuffer.
         */
        RENDER_DEFERRED_FRAMEBUFFER,
        /**
         * Deferred render on the shadow
         */
         RENDER_DEFERRED_SHADOW,
         /**
         * Deferred render on the screen
         */
         RENDER_DEFERRED_SCREEN
    } RenderStep;

    /**
     * An abstract class to drawable object
     * @tparam vecType The dimension of the drawable. Either 2D or 3D.
     */
    template<typename vecType> class Drawable {

    public:
        /**
         * The default construct can't be used
         */
        Drawable() = delete;

        /**
         * The user must give a selection code, even if it is zero or non used
         * @param code The selection buffer code
         */
        explicit Drawable(unsigned int code);

        /**
         * A virtual method which is called to render the drawable
         * @param program The shader to use to draw the object
         * @param renderStep The render step
         */
        virtual void render(std::shared_ptr<Program> program, RenderStep renderStep) const = 0;

        /**
         * @return The selection buffer code of this drawable
         */
        virtual unsigned int getCode();

        /**
         * @param code The code, directly readed from the selection buffer
         * @return Return true if this drawable correspond to this code
         */
        virtual bool is(float code);

    private:
        unsigned int mCode;

    };

    template class Drawable<glm::vec2>;
    template class Drawable<glm::vec3>;

}


#endif //SOLAR_SYSTEM_DRAWABLE_H
