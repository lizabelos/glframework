
#include "OpenglNoel.h"


OpenglNoel::OpenglNoel() : GLTools::Window("Solar System"), mSphere(0, 256, 256), mCube(0), mSquare(0), mMouseSet(false), mTextureManager("res/textures") {

    mRender3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mGeometryProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/geometry/light.fs.glsl");
    mShadingProgram =  std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/default.fs.glsl");

    mScene = std::make_shared<GLScene::Scene>("res/objs/sponza");

    mFreeflyCamera = std::make_shared<GLTools::FreeflyModelView>();
    mFreeflyCamera->setPerspective(mScene->getBoundingBoxDiagonal(), 0.1f);

    mModelView2D = std::make_shared<GLTools::ModelView2D>();


}

void OpenglNoel::render(GLTools::RenderStep renderStep) {

    if (renderStep == GLTools::RENDER_SCREEN) {

        mFreeflyCamera->identity();

        mRender3DProgram->post("uLightPosition", mFreeflyCamera->getViewMatrix() * glm::vec4(0.0f, 5.0f, 2.0f, 1.0f));
        mRender3DProgram->post("uCameraPosition", glm::vec4(mFreeflyCamera->getPosition(), 1.0f));

        mScene->render(*mFreeflyCamera, mRender3DProgram, renderStep);

    }

    if (renderStep == GLTools::RENDER_DEFERRED_FRAMEBUFFER) {


        mFreeflyCamera->identity();

        mScene->render(*mFreeflyCamera, mGeometryProgram, renderStep);


    }

    if (renderStep == GLTools::RENDER_DEFERRED_SCREEN) {

        mModelView2D->identity();

        mShadingProgram->post("uLightPosition", mFreeflyCamera->getViewMatrix() * glm::vec4(0.0f, 5.0f, 2.0f, 1.0f));
        mShadingProgram->post("uCameraPosition", glm::vec4(mFreeflyCamera->getPosition(), 1.0f));

        mSquare.render(*mModelView2D, mShadingProgram, renderStep);

    }

}


void OpenglNoel::keyboard(Uint32 type, bool repeat, int key) {

    switch (key) {
        case SDLK_UP:
        case SDLK_z:
            mFreeflyCamera->moveFront(3.0f);
            break;
        case SDLK_LEFT:
        case SDLK_q:
            mFreeflyCamera->moveLeft(3.0f);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            mFreeflyCamera->moveLeft(-3.0f);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            mFreeflyCamera->moveFront(-3.0f);
            break;
        case SDLK_LSHIFT:
            mFreeflyCamera->moveUp(3.0f);
            break;
        case SDLK_SPACE:
            mFreeflyCamera->moveUp(-3.0f);
            break;
        case SDLK_f:
            setDeferred(true);
            break;
        case SDLK_g:
            setDeferred(false);
            break;
        default:
            break;
    }
    
}

void OpenglNoel::mouseMove(glm::vec2 mousePosition, unsigned int selection) {
    glm::vec2 diff = mousePosition - mMouseStart;
    mMouseStart = mousePosition;
    
    if (mMouseSet) {
        mFreeflyCamera->rotateLeft(diff.x * 2 * M_PI);
        mFreeflyCamera->rotateUp(diff.y * 2 * M_PI);
    } else {
        mMouseSet = true;
    }
}

void OpenglNoel::resize(unsigned int width, unsigned int height) {
    mFreeflyCamera->resize(width, height);
}