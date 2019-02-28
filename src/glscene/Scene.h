//
// Created by thomas on 15/01/19.
// This code is based on the GLMLV Library
//

#ifndef SOLAR_SYSTEM_SCENE_H
#define SOLAR_SYSTEM_SCENE_H

#include <memory>

#include "../gltools/Drawable"
#include "../maths/Variable"
#include "../gltools/Buffer"
#include "../gltools/Program"
#include "../gltools/TextureManager"
#include "../gltools/Buffer"

namespace GLScene {


    class Scene : public GLTools::Drawable<glm::vec3> {

    public:
        explicit Scene(const std::string &path);

        void render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const override;

        float getBoundingBoxDiagonal();

    private:
        GLTools::VertexArrayObject mVertexArrayObject;
        int mSize;


        struct PhongMaterial
        {
            std::string name;

            glm::vec4 Ka = glm::vec4(0); // Ambient multiplier
            glm::vec4 Kd = glm::vec4(0); // Diffuse multiplier
            glm::vec4 Ks = glm::vec4(0); // Glossy multiplier
            float shininess = 0.f; // Glossy exponent

            // Indices in the textures vector:
            std::string KaTextureId = "";
            std::string KdTextureId = "";
            std::string KsTextureId = "";
            std::string shininessTextureId = "";
            std::string normalTextureId = "";
        };

        // Points min et max de la bounding box englobant la scene
        glm::vec3 bboxMin = glm::vec3(std::numeric_limits<float>::max());
        glm::vec3 bboxMax = glm::vec3(std::numeric_limits<float>::lowest());

        std::vector<glm::vec3> mPositions;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec3> mTexCoords;

        std::vector<uint32_t> indexBuffer; // Tableau d'index de sommets

        size_t shapeCount = 0; // Nombre d'objets à dessiner
        std::vector<uint32_t> indexCountPerShape; // Nomber d'index de sommets pour chaque objet
        std::vector<glm::mat4> localToWorldMatrixPerShape; // Matrice localToWorld de chaque objet
        std::vector<int32_t> materialIDPerShape; // Index du materiau de chaque objet (-1 si pas de materiaux)

        std::vector<PhongMaterial> materials; // Tableau des materiaux
        std::shared_ptr<GLTools::TextureManager> mTextureManager;

    };

}


#endif //SOLAR_SYSTEM_SCENE_H
