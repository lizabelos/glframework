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

#include "../external/stb/stb_image.h"
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#include "../external/gltf/tiny_gltf.h"


namespace GLScene {

    class SceneGLTF : public Scene {

    public:
        explicit SceneGLTF(const std::string &path);

        void render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

        float getBoundingBoxDiagonal() override;

    private:
        void bindModelNodes(std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> vbos, tinygltf::Model &model, tinygltf::Node &node);
        std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> bindMesh(std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> vbos, tinygltf::Model &model, tinygltf::Mesh &mesh);

        GLTools::VertexArrayObject mVertexArrayObject;

        tinygltf::TinyGLTF mLoader;
        tinygltf::Model mModel;

    };

}


#endif //BELOSGL_SCENEGLTF_H
