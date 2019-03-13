// This code is based on the GLMLV Library

#include "SceneASSIMP.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <stack>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/ProgressHandler.hpp>

glm::mat4 aiMatrixToGlmMatrix(const aiMatrix4x4 & mat)
{
    auto copy = mat;
    copy.Transpose();
    return glm::mat4(
        copy.a1, copy.a2, copy.a3, copy.a4, 
        copy.b1, copy.b2, copy.b3, copy.b4,
        copy.c1, copy.c2, copy.c3, copy.c4, 
        copy.d1, copy.d2, copy.d3, copy.d4
    );
}

std::string getFileName(std::string filePath, bool withExtension = true)
{

    std::replace( filePath.begin(), filePath.end(), '\\', '/');

    // Get last dot position
    std::size_t dotPos = filePath.rfind('.');
    std::size_t sepPos = filePath.rfind('/');
 
    if(sepPos != std::string::npos)
    {
        return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
    }
    return "";
}


GLScene::SceneASSIMP::SceneASSIMP(const std::string &path) : Scene(0) {

    mTextureManager = std::make_shared<GLTools::TextureManager>(path);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile((path + ".obj").c_str(), aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error(importer.GetErrorString());
    }

    std::stack<std::pair<aiNode*, aiMatrix4x4>> nodes;
    nodes.push(std::make_pair(scene->mRootNode, scene->mRootNode->mTransformation));
    
    const auto materialIdOffset = materials.size();

    while (!nodes.empty())
    {
        const auto node = nodes.top().first;
        const auto localToWorldMatrix = nodes.top().second;
        nodes.pop();

        shapeCount += node->mNumMeshes;

        for (auto meshIdx = 0u; meshIdx < node->mNumMeshes; ++meshIdx)
        {
            aiMesh * mesh = scene->mMeshes[node->mMeshes[meshIdx]];

            const auto indexOffset = mPositions.size();

            for (auto vertexIdx = 0u; vertexIdx < mesh->mNumVertices; ++vertexIdx)
            {
                const float vx = mesh->HasPositions() ? mesh->mVertices[vertexIdx].x : 0.f;
                const float vy = mesh->HasPositions() ? mesh->mVertices[vertexIdx].y : 0.f;
                const float vz = mesh->HasPositions() ? mesh->mVertices[vertexIdx].z : 0.f;
                const float nx = mesh->HasNormals() ? mesh->mNormals[vertexIdx].x : 0.f;
                const float ny = mesh->HasNormals() ? mesh->mNormals[vertexIdx].y : 0.f;
                const float nz = mesh->HasNormals() ? mesh->mNormals[vertexIdx].z : 0.f;

                const float tx = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][vertexIdx].x : 0.f;
                const float ty = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][vertexIdx].y : 0.f;

                mPositions.emplace_back(glm::vec3(vx, vy, vz));
                mNormals.emplace_back(glm::vec3(nx, ny, nz));
                mTexCoords.emplace_back(glm::vec3(tx, ty, 1.0f));
            }

            const auto indexCount = mesh->mNumFaces * 3;
            indexCountPerShape.emplace_back(indexCount);
            localToWorldMatrixPerShape.emplace_back(aiMatrixToGlmMatrix(localToWorldMatrix));
            indexBuffer.reserve(indexBuffer.size() + indexCount);
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                assert(face.mNumIndices == 3);
                for (unsigned int j = 0; j < face.mNumIndices; j++) 
                {
                    const auto index = indexOffset + face.mIndices[j];
                    indexBuffer.emplace_back(index);
                    bboxMin = glm::min(bboxMin, mPositions[index]);
                    bboxMax = glm::max(bboxMax, mPositions[index]);
                }
            }

            materialIDPerShape.emplace_back(mesh->mMaterialIndex >= 0 ? materialIdOffset + mesh->mMaterialIndex : -1);

        }

        for (auto childIdx = 0u; childIdx < node->mNumChildren; ++childIdx) {
            nodes.push(std::make_pair(node->mChildren[childIdx], node->mChildren[childIdx]->mTransformation * localToWorldMatrix));
        }
    }

    // Materials
    materials.reserve(materials.size() + scene->mNumMaterials);
    for (auto materialIdx = 0u; materialIdx < scene->mNumMaterials; ++materialIdx)
    {
        aiMaterial * material = scene->mMaterials[materialIdx];

        materials.emplace_back(); // Add new material
        auto & newMaterial = materials.back();

        aiColor3D color;

        aiString ainame;
        material->Get(AI_MATKEY_NAME, ainame);
        newMaterial.name = ainame.C_Str();

        if (newMaterial.name == "Helmet")
        {
            std::clog << "Material " << newMaterial.name << std::endl;
            std::clog << material->mNumProperties << std::endl;
            for (auto i = 0; i < material->mNumProperties; ++i)
            {
                std::clog << "Property " << material->mProperties[i]->mKey.C_Str() << ", " << material->mProperties[i]->mType << ", " << material->mProperties[i]->mIndex << std::endl;
                if (material->mProperties[i]->mType == aiPTI_String)
                {
                    aiString x;
                    material->Get(material->mProperties[i]->mKey.C_Str(), material->mProperties[i]->mSemantic, material->mProperties[i]->mIndex, x);

                    std::clog << material->mProperties[i]->mKey.C_Str() << ", " << "Value = " << x.C_Str() << std::endl;
                }
            }

            for (auto i = 0; i < material->GetTextureCount(aiTextureType_UNKNOWN); ++i)
            {
                aiString path;
                if (AI_SUCCESS == material->GetTexture(aiTextureType_UNKNOWN, i, &path,
                    nullptr, nullptr, nullptr, nullptr, nullptr)) {
                    std::cerr << "texture " << i << path.C_Str() << std::endl;
                }
            }
        }


        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
            newMaterial.Ka = glm::vec4(color.r, color.g, color.b, 1.0f);
        }

        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
            newMaterial.Kd = glm::vec4(color.r, color.g, color.b, 1.0f);
        }

        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
            newMaterial.Ks = glm::vec4(color.r, color.g, color.b, 1.0f);
        }

        material->Get(AI_MATKEY_SHININESS, newMaterial.shininess);

        aiString path;
        if (AI_SUCCESS == material->GetTexture(aiTextureType_AMBIENT, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr)) {
            newMaterial.KaTextureId = getFileName(path.data);
            std::cout << getFileName(path.data) << std::endl;
        }

        if (AI_SUCCESS == material->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr)) {
            newMaterial.KdTextureId = getFileName(path.data);
        }

        if (AI_SUCCESS == material->GetTexture(aiTextureType_SPECULAR, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr)) {
            newMaterial.KsTextureId = getFileName(path.data);
        }

        if (AI_SUCCESS == material->GetTexture(aiTextureType_SHININESS, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr)) {
            newMaterial.shininessTextureId = getFileName(path.data);
        }

        if (AI_SUCCESS == material->GetTexture(aiTextureType_HEIGHT, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr)) {
            newMaterial.normalTextureId = getFileName(path.data);
        }
 
    }

    mVertexArrayObject.add(VERTEX_ID, std::make_shared<GLTools::ArrayBuffer>(mPositions));
    mVertexArrayObject.add(NORMAL_ID, std::make_shared<GLTools::ArrayBuffer>(mNormals));
    mVertexArrayObject.add(TEXTCOORD_ID, std::make_shared<GLTools::ArrayBuffer>(mTexCoords));
    mVertexArrayObject.set(std::make_shared<GLTools::ElementArrayBuffer>(indexBuffer));

}

void GLScene::SceneASSIMP::render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const {


    program->use();

    mVertexArrayObject.bind();


    int indexOffset = 0, shapeId = 0;
    for (const auto indexCount: indexCountPerShape)
    {
        int32_t materialId = materialIDPerShape[shapeId];
        if (materialId != -1) {
            auto material = materials[materialId];
            program->post("uAmbient", material.Ka);
            program->post("uDiffuse", material.Kd);
            program->post("uSpecular", material.Ks);
            program->post("uShininess", material.shininess);

            if (material.KaTextureId != "") {
                (*mTextureManager)[material.KaTextureId]->activate(GL_TEXTURE0);
                program->postTexture("uAmbientTexture", 0);
                program->post("uAmbientHasTexture", GL_TRUE);
            } else {
                program->post("uAmbientHasTexture", GL_FALSE);
            }

            if (material.KdTextureId != "") {
                (*mTextureManager)[material.KdTextureId]->activate(GL_TEXTURE1);
                program->postTexture("uDiffuseTexture", 1);
                program->post("uDiffuseHasTexture", GL_TRUE);
            } else {
                program->post("uDiffuseHasTexture", GL_FALSE);
            }

            if (material.KsTextureId != "") {
                (*mTextureManager)[material.KsTextureId]->activate(GL_TEXTURE2);
                program->postTexture("uSpecularTexture", 2);
                program->post("uSpecularHasTexture", GL_TRUE);
            } else {
                program->post("uSpecularHasTexture", GL_FALSE);
            }

            if (material.shininessTextureId != "") {
                (*mTextureManager)[material.shininessTextureId]->activate(GL_TEXTURE3);
                program->postTexture("uShininessTexture", 3);
                program->post("uShininessHasTexture", GL_TRUE);
            } else {
                program->post("uShininessHasTexture", GL_FALSE);
            }

            if (material.normalTextureId != "") {
                (*mTextureManager)[material.normalTextureId]->activate(GL_TEXTURE4);
                program->postTexture("uNormalTexture", 4);
                program->post("uNormalHasTexture", GL_TRUE);
            } else {
                program->post("uNormalHasTexture", GL_FALSE);
            }


        } else {
            program->post("uAmbientHasTexture", GL_FALSE);
            program->post("uDiffuseHasTexture", GL_FALSE);
            program->post("uSpecularHasTexture", GL_FALSE);
            program->post("uShininessHasTexture", GL_FALSE);
            program->post("uNormalHasTexture", GL_FALSE);
            program->post("uAmbient", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            program->post("uDiffuse", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            program->post("uSpecular", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            program->post("uShininess", 1.0f);
        }

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const GLvoid*) (indexOffset * sizeof(GLuint)));
        indexOffset += indexCount;
        shapeId += 1;
    }
    
    glBindVertexArray(0);

}

float GLScene::SceneASSIMP::getBoundingBoxDiagonal() {
    return sqrt(pow(bboxMin.x - bboxMax.x,2) + pow(bboxMin.y - bboxMax.y,2) + pow(bboxMin.z - bboxMax.z,2));
}