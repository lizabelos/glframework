//
// Created by thomas on 11/14/18.
//

#ifndef SOLAR_SYSTEM_VERTEXDRAWABLE_H
#define SOLAR_SYSTEM_VERTEXDRAWABLE_H

#include <memory>

#include "Drawable"
#include "Variable"
#include "Buffer"
#include "Program"


namespace GLTools {

    class ParametricDrawable : public Drawable {

    public:
        void initialize(Variable x, Variable y, Variable z, Variable normX, Variable normY, Variable normZ, Variable texX, Variable texY, SVariable p1, SVariable p2, unsigned long resolution1, unsigned long resolution2);
        void render(const Camera &camera) const override;

    protected:
        std::vector<GLuint> getIndices(unsigned long resolution1, unsigned long resolution2) const;
        GLsizei getIndicesNumber(unsigned long resolution1, unsigned long resolution2) const;

    private:
        unsigned long mSize, mResolution1, mResolution2;
        VertexArrayObject mVertexArrayObject;

    };

}


#endif //SOLAR_SYSTEM_VERTEXDRAWABLE_H
