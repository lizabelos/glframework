//
// Created by thomas on 11/26/18.
//

#ifndef TANGRAM_TANGRAM_H
#define TANGRAM_TANGRAM_H

#include "gltools/Window"
#include "gltools/Camera"
#include "glgeometry/Circle"
#include "glgeometry/Triangle"

class Tangram : public GLTools::Window {

public:
    Tangram();

    void render(GLTools::RenderStep renderStep) override;

protected:
    void resize(unsigned int width, unsigned int height) override;
    void mouseClick(int mouseX, int mouseY, Uint8 state, Uint8 button, unsigned int selection) override;

private:
    GLTools::Camera2D mCamera;
    GLGeometry::Circle mCircle;
    GLGeometry::Triangle mTriangle;

    std::unique_ptr<GLTools::Program> mBasicProgram;

};


#endif //TANGRAM_TANGRAM_H
