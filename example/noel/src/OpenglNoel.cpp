
#include "OpenglNoel.h"

#include <iostream>

OpenglNoel::OpenglNoel() : GLTools::Window("Solar System"), mSphere(0, 256, 256), mCube(0), mMouseSet(false), mTextureManager("res/textures") {

    mSquare = std::make_shared<GLGeometry::Square>(0);

    mRender3DProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/basic3d.fs.glsl");
    mGeometryProgram = std::make_shared<GLTools::Program>("res/shaders/basic3d.vs.glsl", "res/shaders/geometry/default.fs.glsl");

    mShadingProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/default.fs.glsl");
    mShadingAmbienProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/ambient.fs.glsl");
    mShadingDiffuseProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/diffuse.fs.glsl");
    mShadingNormalProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/normal.fs.glsl");
    mShadingShadowProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/shadow.fs.glsl");
    mShadingSpecularProgram = std::make_shared<GLTools::Program>("res/shaders/shading/default.vs.glsl", "res/shaders/shading/specular.fs.glsl");


    mShadowProgram = std::make_shared<GLTools::Program>("res/shaders/shadow/directionalSM.vs.glsl", "res/shaders/shadow/directionalSM.fs.glsl");

    mScene = std::make_shared<GLScene::Scene>("res/objs/sponza");

    mFreeflyCamera = std::make_shared<GLTools::FreeflyModelView>();
    mFreeflyCamera->setPerspective(mScene->getBoundingBoxDiagonal(), 0.1f);

    mLightView = std::make_shared<GLTools::FreeflyModelView>();
    // todo : ortogprahic projection
    mLightView->setOrthographic(mScene->getBoundingBoxDiagonal());
    //mLightView->moveUp(mScene->getBoundingBoxDiagonal() / 4);
    mLightView->rotateUp(-M_PI/2);

    mModelView2D = std::make_shared<GLTools::ModelView2D>();


}

void OpenglNoel::render(GLTools::RenderStep renderStep) {

    if (renderStep == GLTools::RENDER_SCREEN) {

        mFreeflyCamera->identity();

        mRender3DProgram->post("uLightPosition", mFreeflyCamera->getViewMatrix() * glm::vec4(mLightView->getPosition(), 1.0f));
        mRender3DProgram->post("uCameraPosition", glm::vec4(mFreeflyCamera->getPosition(), 1.0f));

        mScene->render(*mFreeflyCamera, mRender3DProgram, renderStep);
        renderLight(mRender3DProgram, renderStep);

    }

    if (renderStep == GLTools::RENDER_DEFERRED_FRAMEBUFFER) {

        mFreeflyCamera->identity();
        mScene->render(*mFreeflyCamera, mGeometryProgram, renderStep);
        renderLight(mGeometryProgram, renderStep);


    }

    if (renderStep == GLTools::RENDER_DEFERRED_SHADOW) {

        mFreeflyCamera->identity();
        mScene->render(*mLightView, mShadowProgram, renderStep);
    }

    if (renderStep == GLTools::RENDER_DEFERRED_SCREEN) {

        mModelView2D->identity();

        if (mSplittedMode) {

            renderDeferred(mShadingAmbienProgram, glm::vec2(-2.0 / 3.0,-1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));
            renderDeferred(mShadingDiffuseProgram, glm::vec2(-0.0 / 3.0,-1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));
            renderDeferred(mShadingNormalProgram, glm::vec2(2.0 / 3.0,-1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));
            renderDeferred(mShadingShadowProgram, glm::vec2(-2.0 / 3.0,1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));
            renderDeferred(mShadingSpecularProgram, glm::vec2(0.0 / 3.0,1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));
            renderDeferred(mShadingProgram, glm::vec2(2.0 / 3.0,1.0 / 2.0), glm::vec2(1.0 / 3.0,1.0 / 2.0));

        } else {
            renderDeferred(mShadingProgram, glm::vec2(0,0), glm::vec2(1,1));

        }


    }

}

void OpenglNoel::renderLight(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) {
    mFreeflyCamera->pushMatrix();

    mFreeflyCamera->translate(mLightView->getPosition());
    mFreeflyCamera->scale(10.0f);

    program->post("uAmbientHasTexture", GL_FALSE);
    program->post("uDiffuseHasTexture", GL_FALSE);
    program->post("uSpecularHasTexture", GL_FALSE);
    program->post("uShininessHasTexture", GL_FALSE);
    program->post("uNormalHasTexture", GL_FALSE);
    program->post("uAmbient", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uDiffuse", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uSpecular", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uShininess", 1.0f);

    mSphere.render(*mFreeflyCamera, program, renderStep);


    mFreeflyCamera->popMatrix();
}


void OpenglNoel::renderDeferred(std::shared_ptr<GLTools::Program> program, glm::vec2 position, glm::vec2 size) {

    program->post("uLightPosition", mFreeflyCamera->getViewMatrix() * glm::vec4(mLightView->getPosition(), 1.0f));
    program->post("uCameraPosition", glm::vec4(mFreeflyCamera->getPosition(), 1.0f));
    program->post("uLight", *mLightView);
    program->post("uLightMVPMatrix", ( mLightView->getProjectionMatrix() * mLightView->getViewMatrix() * glm::inverse(mFreeflyCamera->getViewMatrix())));
    program->post("uLightShadowMapBias",  0.005f);
    program->postTexture("uGPosition", 0);
    program->postTexture("uGNormal", 1);
    program->postTexture("uGAmbient", 2);
    program->postTexture("uGDiffuse", 3);
    program->postTexture("uGlossyShininess", 4);
    program->postTexture("uGShadow", 5);

    mModelView2D->pushMatrix();

   // mModelView2D->translate(glm::vec2(-2.0/3.0,-0.5));
    mModelView2D->translate(position);
    mModelView2D->scale(size);



    //mModelView2D->translate(position);

    mSquare->render(*mModelView2D, program, GLTools::RENDER_DEFERRED_SCREEN);
    mModelView2D->popMatrix();

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
        case SDLK_i:
            mLightView->moveFront(3.0f);
            break;
        case SDLK_j:
            mLightView->moveLeft(3.0f);
            break;
        case SDLK_l:
            mLightView->moveLeft(-3.0f);
            break;
        case SDLK_k:
            mLightView->moveFront(-3.0f);
            break;
        case SDLK_p:
            mLightView->moveUp(3.0f);
            break;
        case SDLK_m:
            mLightView->moveUp(-3.0f);
            break;
        case SDLK_LSHIFT:
            mFreeflyCamera->moveUp(3.0f);
            break;
        case SDLK_SPACE:
            mFreeflyCamera->moveUp(-3.0f);
            break;
        case SDLK_h:
            setDeferred(true);
            mSplittedMode = true;
            std::cout << "Set splitted mode to true" << std::endl;
            break;
        case SDLK_f:
            setDeferred(true);
            mSplittedMode = false;
            break;
        case SDLK_g:
            setDeferred(false);
            mSplittedMode = false;
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
    //mModelView2D->resize(width, height);
}

bool OpenglNoel::needRenderShadow() {
    return true;
}