
#include "OpenglNoel.h"
#include "external/imgui/imgui.h"

#include <iostream>

OpenglNoel::OpenglNoel() : GLTools::Window("Solar System"), mSphere(0, 256, 256), mCube(0), mSquare(0), mMouseSet(false), mTextureManager("res/textures") {

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

    mShadowProjection = GLTools::OrthographicProjection(mScene->getBoundingBoxDiagonal());
    mShadowView = GLTools::LightView(glm::vec3(0, 0, 0), mScene->getBoundingBoxDiagonal(), 90, 90, glm::vec3(0, 0, -1));

}

void OpenglNoel::render(GLTools::RenderStep renderStep) {

    if (renderStep == GLTools::RENDER_SCREEN) {

        mModel.identity();

        mRender3DProgram->post("uLightPosition", mCamera.getMatrix() * glm::vec4(mShadowView.getLightPosition(), 1.0f));
        mRender3DProgram->post("uCameraPosition", glm::vec4(mCamera.getPosition(), 1.0f));
        mRender3DProgram->post(mProjection, mModel, mCamera);

        mScene->render(mRender3DProgram, renderStep);
        renderLight(mRender3DProgram, renderStep);
        renderGui(renderStep);

    }

    if (renderStep == GLTools::RENDER_DEFERRED_FRAMEBUFFER) {

        mModel.identity();

        mGeometryProgram->post(mProjection, mModel, mCamera);
        mScene->render(mGeometryProgram, renderStep);
        renderLight(mGeometryProgram, renderStep);


    }

    if (renderStep == GLTools::RENDER_DEFERRED_SHADOW) {

        mModel.identity();

        mShadowProgram->post(mShadowProjection, mModel, mShadowView);
        mScene->render(mShadowProgram, renderStep);
    }

    if (renderStep == GLTools::RENDER_DEFERRED_SCREEN) {

        mModel2D.identity();

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

        renderGui(renderStep);


    }

}

void OpenglNoel::renderLight(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) {/*
    mModel.pushMatrix();

    mModel.translate(mShadowView.getLightPosition());
    mModel.scale(10.0f);

    program->post("uAmbientHasTexture", GL_FALSE);
    program->post("uDiffuseHasTexture", GL_FALSE);
    program->post("uSpecularHasTexture", GL_FALSE);
    program->post("uShininessHasTexture", GL_FALSE);
    program->post("uNormalHasTexture", GL_FALSE);
    program->post("uAmbient", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uDiffuse", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uSpecular", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uShininess", 1.0f);
    program->post(mProjection, mModel, mCamera);

    mSphere.render(program, renderStep);

    mModel.popMatrix();*/
}


void OpenglNoel::renderDeferred(std::shared_ptr<GLTools::Program> program, glm::vec2 position, glm::vec2 size) {

    program->post("uLightPosition", mCamera.getMatrix() * glm::vec4(mShadowView.getLightPosition(), 1.0f));
    program->post("uCameraPosition", glm::vec4(mCamera.getPosition(), 1.0f));
    program->post("uLight", mShadowView.getMatrix());
    program->post("uLightMVPMatrix", ( mShadowProjection.getMatrix() * mShadowView.getMatrix() * glm::inverse(mCamera.getMatrix())));
    program->post("uLightShadowMapBias",  0.005f);
    program->postTexture("uGPosition", 0);
    program->postTexture("uGNormal", 1);
    program->postTexture("uGAmbient", 2);
    program->postTexture("uGDiffuse", 3);
    program->postTexture("uGlossyShininess", 4);
    program->postTexture("uGShadow", 5);

    mModel2D.pushMatrix();

   // mModelView2D->translate(glm::vec2(-2.0/3.0,-0.5));
    mModel2D.translate(position);
    mModel2D.scale(size);


    program->post(mModel2D);
    //mModelView2D->translate(position);

    mSquare.render(program, GLTools::RENDER_DEFERRED_SCREEN);
    mModel2D.popMatrix();

}

void OpenglNoel::renderGui(GLTools::RenderStep renderStep) {

    newImguiFrame();

    float my_color[4] = {0.45f, 0.55f, 0.60f, 1.00f};
    bool my_tool_active = true;

    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

// Edit a color (stored as ~4 floats)
    ImGui::ColorEdit4("Color", my_color);

// Plot some values
    const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
    ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

// Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void OpenglNoel::keyboard(Uint32 type, bool repeat, int key) {

    switch (key) {
        case SDLK_UP:
        case SDLK_z:
            mCamera.moveFront(3.0f);
            break;
        case SDLK_LEFT:
        case SDLK_q:
            mCamera.moveLeft(3.0f);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            mCamera.moveLeft(-3.0f);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            mCamera.moveFront(-3.0f);
            break;
        case SDLK_i:
            mShadowView.moveFront(3.0f);
            break;
        case SDLK_j:
            mShadowView.moveLeft(3.0f);
            break;
        case SDLK_l:
            mShadowView.moveLeft(-3.0f);
            break;
        case SDLK_k:
            mShadowView.moveFront(-3.0f);
            break;
        case SDLK_p:
            mShadowView.moveUp(3.0f);
            break;
        case SDLK_m:
            mShadowView.moveUp(-3.0f);
            break;
        case SDLK_LSHIFT:
            mCamera.moveUp(3.0f);
            break;
        case SDLK_SPACE:
            mCamera.moveUp(-3.0f);
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
        mCamera.rotateLeft(diff.x * 2 * M_PI);
        mCamera.rotateUp(diff.y * 2 * M_PI);
    } else {
        mMouseSet = true;
    }
}

void OpenglNoel::resize(unsigned int width, unsigned int height) {
    mProjection = GLTools::PerspectiveProjection(width, height, 0.1f, mScene->getBoundingBoxDiagonal());
}

bool OpenglNoel::needRenderShadow() {
    return true;
}