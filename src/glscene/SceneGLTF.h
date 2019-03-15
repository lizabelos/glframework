//
// Created by thomas on 13/03/19.
//

#ifndef BELOSGL_SCENEGLTF_H
#define BELOSGL_SCENEGLTF_H

#include "Scene"
#include "../gltools/Drawable"
#include "../maths/Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"
#include "../gltools/TextureManager"
#include "../gltools/Buffer"

#include "../external/gltf/tiny_gltf.h"


namespace GLScene {

    class SceneGLTFPrimitive;

    class SceneGLTF : public Scene {

    public:
        explicit SceneGLTF(const std::string &path);

        void render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

        float getBoundingBoxDiagonal() override;

    private:
        friend class SceneGLTFPrimitive;

        std::vector<std::unique_ptr<SceneGLTFPrimitive>> mPrimitives;

        tinygltf::TinyGLTF mLoader;
        tinygltf::Model mModel;

    };

    class SceneGLTFPrimitive : public GLTools::Drawable<glm::vec3> {

    public:
        explicit SceneGLTFPrimitive(const SceneGLTF &parent, const tinygltf::Primitive &primitive);

        void render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

        glm::vec3 getBoxMin();
        glm::vec3 getBoxMax();

    private:
        void loadIndices();
        void loadTriangles();
        std::vector<glm::vec3> loadVertexs(const tinygltf::Accessor &accessor);

        const SceneGLTF &mParent;
        const tinygltf::Primitive &mPrimitive;

        GLTools::VertexArrayObject mVertexArrayObject;

        int mSize;

        glm::vec3 mBoxMin = glm::vec3(0.0f, 0.0f, 0.0f), mBoxMax = glm::vec3(0.0f, 0.0f, 0.0f);

    };

}


#endif //BELOSGL_SCENEGLTF_H
