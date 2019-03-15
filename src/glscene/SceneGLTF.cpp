//
// Created by thomas on 13/03/19.
// Inspired by https://github.com/lighttransport/nanort/blob/master/examples/pbr_surface/gltf-loader.cc

#include "SceneGLTF.h"
#include "../maths/Array"

#include "../external/stb/stb_image.h"
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/gltf/tiny_gltf.h"

#include <iostream>
#include <stdexcept>

static std::string GetFilePathExtension(const std::string &FileName) {
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

GLScene::SceneGLTF::SceneGLTF(const std::string &path) : Scene(0) {
    std::string err;
    std::string warn;

    const std::string ext = GetFilePathExtension(path);

    bool ret = mLoader.LoadBinaryFromFile(&mModel, &err, &warn, path);

    if (!warn.empty()) {
        std::cerr << "Warning : " << warn.c_str() << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "Error : " << err.c_str() << std::endl;
    }

    if (!ret) {
        throw std::runtime_error("can't load gltf scene");
    }

    std::cout << "loaded glTF file has:\n"
              << mModel.accessors.size() << " accessors\n"
              << mModel.animations.size() << " animations\n"
              << mModel.buffers.size() << " buffers\n"
              << mModel.bufferViews.size() << " bufferViews\n"
              << mModel.materials.size() << " materials\n"
              << mModel.meshes.size() << " meshes\n"
              << mModel.nodes.size() << " nodes\n"
              << mModel.textures.size() << " textures\n"
              << mModel.images.size() << " images\n"
              << mModel.skins.size() << " skins\n"
              << mModel.samplers.size() << " samplers\n"
              << mModel.cameras.size() << " cameras\n"
              << mModel.scenes.size() << " scenes\n"
              << mModel.lights.size() << " lights\n";


    for (const auto &meshe : mModel.meshes) {

        for (const auto &primitive : meshe.primitives) {

            mPrimitives.emplace_back(std::make_unique<SceneGLTFPrimitive>(*this, primitive));

        }

    }


}

void GLScene::SceneGLTF::render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const {

    program->postTexture("uAmbientTexture", 0);
    program->post("uAmbientHasTexture", GL_FALSE);
    program->post("uDiffuseHasTexture", GL_FALSE);
    program->post("uSpecularHasTexture", GL_FALSE);
    program->post("uShininessHasTexture", GL_FALSE);
    program->post("uNormalHasTexture", GL_FALSE);
    program->post("uAmbient", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uDiffuse", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uSpecular", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program->post("uShininess", 1.0f);

    for (const std::unique_ptr<SceneGLTFPrimitive> &primitive : mPrimitives) {
        primitive->render(program, renderStep);
    }

}

float GLScene::SceneGLTF::getBoundingBoxDiagonal() {
    glm::vec3 boxMin = glm::vec3(0,0,0), boxMax = glm::vec3(0,0,0);

    for (const std::unique_ptr<SceneGLTFPrimitive> &primitive : mPrimitives) {
        if (primitive->getBoxMin().x < boxMin.x) boxMin.x = primitive->getBoxMin().x;
        if (primitive->getBoxMin().y < boxMin.x) boxMin.y = primitive->getBoxMin().y;
        if (primitive->getBoxMin().z < boxMin.x) boxMin.z = primitive->getBoxMin().z;
        if (primitive->getBoxMax().x > boxMax.x) boxMax.x = primitive->getBoxMax().x;
        if (primitive->getBoxMax().y > boxMax.x) boxMax.y = primitive->getBoxMax().y;
        if (primitive->getBoxMax().z > boxMax.x) boxMax.z = primitive->getBoxMax().z;
    }


    return glm::distance(boxMin, boxMax);
}

GLScene::SceneGLTFPrimitive::SceneGLTFPrimitive(const GLScene::SceneGLTF &parent, const tinygltf::Primitive &primitive) : GLTools::Drawable<glm::vec3>(0), mParent(parent), mPrimitive(primitive) {
    loadIndices();
    loadTriangles();
}

void GLScene::SceneGLTFPrimitive::loadIndices() {
    const auto &indicesAccessor = mParent.mModel.accessors[mPrimitive.indices];
    const auto &bufferView = mParent.mModel.bufferViews[indicesAccessor.bufferView];
    const auto &buffer = mParent.mModel.buffers[bufferView.buffer];
    const auto dataAddress = buffer.data.data() + bufferView.byteOffset + indicesAccessor.byteOffset;
    const auto byteStride = indicesAccessor.ByteStride(bufferView);
    const auto count = indicesAccessor.count;

    std::unique_ptr<Maths::intArrayBase> indicesArrayPtr = nullptr;
    switch (indicesAccessor.componentType) {
        case TINYGLTF_COMPONENT_TYPE_BYTE:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<char>>(new Maths::intArray<char>(Maths::arrayAdapter<char>(dataAddress, count, byteStride)));
            break;

        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<unsigned char> >(new Maths::intArray<unsigned char>(Maths::arrayAdapter<unsigned char>(dataAddress, count, byteStride)));
            break;

        case TINYGLTF_COMPONENT_TYPE_SHORT:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<short> >(new Maths::intArray<short>(Maths::arrayAdapter<short>(dataAddress, count, byteStride)));
            break;

        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<unsigned short> >(new Maths::intArray<unsigned short>(Maths::arrayAdapter<unsigned short>(dataAddress, count, byteStride)));
            break;

        case TINYGLTF_COMPONENT_TYPE_INT:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<int> >(new Maths::intArray<int>(Maths::arrayAdapter<int>(dataAddress, count, byteStride)));
            break;

        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            indicesArrayPtr = std::unique_ptr<Maths::intArray<unsigned int> >(new Maths::intArray<unsigned int>(Maths::arrayAdapter<unsigned int>(dataAddress, count, byteStride)));
            break;
        default:
            throw std::runtime_error("Incompatible component type");
    }
    const auto &indices = *indicesArrayPtr;

    std::vector<uint32_t> indicesVector;
    for (size_t i(0); i < indicesArrayPtr->size(); ++i) {
        indicesVector.emplace_back(indices[i]);
    }

    mVertexArrayObject.set(std::make_shared<GLTools::ElementArrayBuffer>(indicesVector));
    mSize = indicesVector.size();
}

void GLScene::SceneGLTFPrimitive::loadTriangles() {
    switch (mPrimitive.mode) {
        case TINYGLTF_MODE_TRIANGLES:

            for (const auto &attribute : mPrimitive.attributes) {
                const auto attribAccessor = mParent.mModel.accessors[attribute.second];
                const auto &bufferView = mParent.mModel.bufferViews[attribAccessor.bufferView];
                const auto &buffer = mParent.mModel.buffers[bufferView.buffer];
                const auto dataPtr = buffer.data.data() + bufferView.byteOffset +
                                     attribAccessor.byteOffset;
                const auto byte_stride = attribAccessor.ByteStride(bufferView);
                const auto count = attribAccessor.count;

                std::cout << "current attribute has count " << count << " and stride " << byte_stride << " bytes\n";
                std::cout << "attribute string is : " << attribute.first << '\n';

                std::vector<glm::vec3> vertexs = loadVertexs(attribAccessor);

                if (attribute.first == "POSITION") {
                    mVertexArrayObject.add(VERTEX_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
                    for (glm::vec3 v : vertexs) {
                        if (v.x < mBoxMin.x) mBoxMin.x = v.x;
                        if (v.y < mBoxMin.y) mBoxMin.y = v.y;
                        if (v.z < mBoxMin.z) mBoxMin.z = v.z;
                        if (v.x > mBoxMax.x) mBoxMax.x = v.x;
                        if (v.y > mBoxMax.y) mBoxMax.y = v.y;
                        if (v.z > mBoxMax.z) mBoxMax.z = v.z;
                    }
                }

                if (attribute.first == "TEXCOORD_0") {
                    mVertexArrayObject.add(TEXTCOORD_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
                }

                if (attribute.first == "NORMAL") {
                    mVertexArrayObject.add(NORMAL_ID, std::make_shared<GLTools::ArrayBuffer>(vertexs));
                }

            }

            break;
        default:
            throw std::runtime_error("Incompatible primitive mode");
    }
}

std::vector<glm::vec3> GLScene::SceneGLTFPrimitive::loadVertexs(const tinygltf::Accessor &accessor) {
    std::vector<glm::vec3> vertexs;

    const auto &bufferView = mParent.mModel.bufferViews[accessor.bufferView];
    const auto &buffer = mParent.mModel.buffers[bufferView.buffer];
    const auto dataPtr = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;
    const auto byte_stride = accessor.ByteStride(bufferView);
    const auto count = accessor.count;


    switch (accessor.type) {

        case TINYGLTF_TYPE_VEC3:
            switch (accessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_FLOAT:
                {
                    Maths::v3fArray positions(Maths::arrayAdapter<Maths::v3f>(dataPtr, count, byte_stride));
                    for (size_t i{0}; i < positions.size(); ++i) {
                        const auto v = positions[i];
                        vertexs.emplace_back(glm::vec3(v.x, v.y, v.z));
                    }
                }
                    break;
                case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                {
                    Maths::v3dArray positions(Maths::arrayAdapter<Maths::v3d>(dataPtr, count, byte_stride));
                    for (size_t i{0}; i < positions.size(); ++i) {
                        const auto v = positions[i];
                        vertexs.emplace_back(glm::vec3(v.x, v.y, v.z));
                    }
                }
                    break;
                default:
                    throw std::runtime_error("Incompatible accessor component type");
            }

            break;

        case TINYGLTF_TYPE_VEC2:
            switch (accessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_FLOAT:
                {
                    Maths::v2fArray positions(Maths::arrayAdapter<Maths::v2f>(dataPtr, count, byte_stride));
                    for (size_t i{0}; i < positions.size(); ++i) {
                        const auto v = positions[i];
                        vertexs.emplace_back(glm::vec3(v.x, v.y, 1.0f));
                    }
                }
                    break;
                case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                {
                    Maths::v2dArray positions(Maths::arrayAdapter<Maths::v2d>(dataPtr, count, byte_stride));
                    for (size_t i{0}; i < positions.size(); ++i) {
                        const auto v = positions[i];
                        vertexs.emplace_back(glm::vec3(v.x, v.y, 1.0f));
                    }
                }
                    break;
                default:
                    throw std::runtime_error("Incompatible accessor component type");
            }

            break;

        default:
            throw std::runtime_error("Incompatible accessor type");
    }

    return vertexs;
}

void GLScene::SceneGLTFPrimitive::render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const {
    program->use();

    mVertexArrayObject.bind();
    glDrawElements(GL_QUADS, mSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 GLScene::SceneGLTFPrimitive::getBoxMin() {
    return mBoxMin;
}

glm::vec3 GLScene::SceneGLTFPrimitive::getBoxMax() {
    return mBoxMax;
}
