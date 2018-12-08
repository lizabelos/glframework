// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_VERTEXDRAWABLE_H
#define SOLAR_SYSTEM_VERTEXDRAWABLE_H

#include <memory>

#include "../gltools/Drawable"
#include "Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"


namespace GLGeometry {

    class ParametricDrawable3D : public GLTools::Drawable<glm::vec3> {

    public:
        explicit ParametricDrawable3D(unsigned int code);

        void initialize(Variable x, Variable y, Variable z, Variable normX, Variable normY, Variable normZ, Variable texX, Variable texY, SVariable p1, SVariable p2, unsigned long resolution1, unsigned long resolution2);

        void render(GLTools::Camera<glm::vec3> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

    protected:
        std::vector<GLuint> getIndices(unsigned long resolution1, unsigned long resolution2) const;
        GLsizei getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const;

    private:
        unsigned long mSize, mResolution1, mResolution2;
        GLTools::VertexArrayObject mVertexArrayObject;

    };

    class ParametricDrawable2D : public GLTools::Drawable<glm::vec2> {

    public:
        explicit ParametricDrawable2D(unsigned int code);

        void initialize(Variable x, Variable y, Variable texX, Variable texY, SVariable p1, SVariable p2, unsigned long resolution1, unsigned long resolution2);

        void render(GLTools::Camera<glm::vec2> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

    protected:
        std::vector<GLuint> getIndices(unsigned long resolution1, unsigned long resolution2) const;
        GLsizei getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const;

    private:
        unsigned long mSize, mResolution1, mResolution2;
        GLTools::VertexArrayObject mVertexArrayObject;

    };

}


#endif //SOLAR_SYSTEM_VERTEXDRAWABLE_H
