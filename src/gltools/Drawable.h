//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_DRAWABLE_H
#define SOLAR_SYSTEM_DRAWABLE_H

#include <vector>
#include <memory>

#include "Camera"
#include "Program"

namespace GLTools {

    typedef enum RenderStep {
        RENDER_SCREEN, RENDER_SELECTION
    } RenderStep;

    template<typename vecType> class Drawable {

    public:
        Drawable() = delete;
        explicit Drawable(unsigned int code);

        virtual void render(Camera <vecType> &camera, std::shared_ptr<Program> program, RenderStep renderStep) const = 0;

        virtual unsigned int getCode();
        virtual bool is(float code);

    private:
        unsigned int mCode;

    };

    template<typename vecType> class TranslatedDrawable : public Drawable<vecType> {

    public:
        TranslatedDrawable(std::shared_ptr<Drawable<vecType>> drawable, vecType translation);

        void render(Camera <vecType> &camera, std::shared_ptr<Program> program, RenderStep renderStep) const override;

        unsigned int getCode() override;
        bool is(float code) override;

        void move(vecType translation);

    private:
        std::shared_ptr<Drawable<vecType>> mDrawable;
        vecType mTranslation;
    };

    template class TranslatedDrawable<glm::vec2>;
    template class TranslatedDrawable<glm::vec3>;

}


#endif //SOLAR_SYSTEM_DRAWABLE_H
