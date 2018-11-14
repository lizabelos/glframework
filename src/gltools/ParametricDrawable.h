//
// Created by thomas on 11/14/18.
//

#ifndef SOLAR_SYSTEM_VERTEXDRAWABLE_H
#define SOLAR_SYSTEM_VERTEXDRAWABLE_H

#include <memory>

#include "Drawable"
#include "Variable"
#include "Buffer"

#define VERTEX_ID 0
#define NORMAL_ID 1
#define TEXTCOORD_ID 2

namespace GLTools {

    class ParametricDrawable : public Drawable {

    public:
        void initialize(AbstractVariable &x, AbstractVariable &y, AbstractVariable &z, AbstractVariable &normX, AbstractVariable &normY, AbstractVariable &normZ, SettableVariable &p1, SettableVariable &p2, unsigned long resolution1, unsigned long resolution2);
        void render(const Camera &camera) const override;

    private:
        std::shared_ptr<ArrayBuffer> mVertexBuffer, mNormalBuffer, mTextcoordBuffer;
        VertexArrayObject mVertexArrayObject;

    };

}


#endif //SOLAR_SYSTEM_VERTEXDRAWABLE_H
