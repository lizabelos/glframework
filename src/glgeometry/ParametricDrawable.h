// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_VERTEXDRAWABLE_H
#define SOLAR_SYSTEM_VERTEXDRAWABLE_H

#include <memory>

#include "../gltools/Drawable"
#include "../maths/Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"


namespace GLGeometry {

    class ParametricDrawable3D : public GLTools::Drawable<glm::vec3> {

    public:
        explicit ParametricDrawable3D(unsigned int code, bool isStatic = true);

        void initialize(Maths::Variable x, Maths::Variable y, Maths::Variable z, Maths::Variable normX, Maths::Variable normY, Maths::Variable normZ, Maths::Variable texX, Maths::Variable texY, Maths::SVariable p1, Maths::SVariable p2, unsigned long resolution1, unsigned long resolution2);

        void render(GLTools::ModelView<glm::vec3> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;
        bool setLine(bool useLine);

    protected:
        std::vector<GLuint> getIndices(unsigned long resolution1, unsigned long resolution2) const;
        GLsizei getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const;

    private:
        unsigned long mSize, mResolution1, mResolution2;
        std::shared_ptr<GLTools::ArrayBuffer> mVertexBuffer, mNormalBuffer, mTexCoordBuffer;
        GLTools::VertexArrayObject mVertexArrayObject;
        bool mUseLine;
        bool mIsInit;
        bool mStatic;

    };

    class ParametricDrawable2D : public GLTools::Drawable<glm::vec2> {

    public:
        explicit ParametricDrawable2D(unsigned int code, bool isStatic = true);

        void initialize(Maths::Variable x, Maths::Variable y, Maths::Variable texX, Maths::Variable texY, Maths::SVariable p1, Maths::SVariable p2, unsigned long resolution1, unsigned long resolution2);

        void render(GLTools::ModelView<glm::vec2> &camera, std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;
        bool setLine(bool useLine);


    protected:
        std::vector<GLuint> getIndices(unsigned long resolution1, unsigned long resolution2) const;
        GLsizei getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const;

    private:
        unsigned long mSize, mResolution1, mResolution2;
        std::shared_ptr<GLTools::ArrayBuffer> mVertexBuffer, mNormalBuffer, mTexCoordBuffer;
        GLTools::VertexArrayObject mVertexArrayObject;
        bool mUseLine;
        bool mIsInit;
        bool mStatic;

    };

}


#endif //SOLAR_SYSTEM_VERTEXDRAWABLE_H
