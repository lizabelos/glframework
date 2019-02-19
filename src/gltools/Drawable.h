// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_DRAWABLE_H
#define SOLAR_SYSTEM_DRAWABLE_H

#include <vector>
#include <memory>

#include "Camera"
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
         * @param camera The camera according to the dimension of the drawable
         * @param program The shader to use to draw the object
         * @param renderStep The render step
         */
        virtual void render(ModelView <vecType> &camera, std::shared_ptr<Program> program, RenderStep renderStep) const = 0;

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

    /**
     * A Scale --> Rotate --> Translate drawable proxy
     * @tparam vecType The dimension of the drawable. Either 2D or 3D.
     */
    template<typename vecType> class TransformDrawable : public Drawable<vecType> {

    public:
        /**
         * Default constructor for transform drawable. The selection id will be copied from the son drawable.
         * @param drawable A shared pointer to the drawable to transform during the rendering
         */
        TransformDrawable(std::shared_ptr<Drawable<vecType>> drawable);

        /**
         * Render the son drawable
         * @param camera The camera according to the dimension of the drawable
         * @param program The shader to use to draw the object
         * @param renderStep The render step
         */
        void render(ModelView <vecType> &camera, std::shared_ptr<Program> program, RenderStep renderStep) const override;

        /**
         * @return The selection buffer code of the son drawable
         */
        unsigned int getCode() override;

        /**
         * @param code The code, directly readed from the selection buffer
         * @return Return true if the son drawable correspond to this code
         */
        bool is(float code) override;

        /**
         * Move the drawable
         * @param translation The movement vector
         */
        void move(vecType translation);

        /**
         * Scale the drawable
         * @param scale The scale vector
         */
        void scale(vecType scale);

        /**
         * Rotate the drawable
         * @param rotation The rotation angle
         * @param rotationAxis The rotation axis (for 3D only)
         */
        void rotate(float rotation, vecType rotationAxis);

        /**
         * @return The current translation
         */
        vecType getTranslation();

        /**
         * @return The current scale
         */
        vecType getScale();

        /**
         * @param translation The new translation
         */
        void setTranslation(vecType translation);


    private:
        std::shared_ptr<Drawable<vecType>> mDrawable;
        vecType mTranslation;
        vecType mScale;
        float mRotation;
        vecType mRotationAxis;
    };

    template class TransformDrawable<glm::vec2>;
    template class TransformDrawable<glm::vec3>;

}


#endif //SOLAR_SYSTEM_DRAWABLE_H
