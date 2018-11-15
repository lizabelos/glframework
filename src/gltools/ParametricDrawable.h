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
        void initialize(AbstractVariable &x, AbstractVariable &y, AbstractVariable &z, AbstractVariable &normX, AbstractVariable &normY, AbstractVariable &normZ, GLTools::AbstractVariable &texX, GLTools::AbstractVariable &texY, SettableVariable &p1, SettableVariable &p2, unsigned long resolution1, unsigned long resolution2);
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
