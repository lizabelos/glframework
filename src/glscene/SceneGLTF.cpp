//
// Created by thomas on 13/03/19.
//

#include "SceneGLTF.h"

#include <iostream>
#include <stdexcept>

GLScene::SceneGLTF::SceneGLTF(const std::string &path) : Scene(0) {
    std::string err;
    std::string warn;
    bool ret = mLoader.LoadASCIIFromFile(&mModel, &err, &warn, path);

    if (!warn.empty()) {
        std::cerr << "Warning : " << warn.c_str() << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "Error : " << err.c_str() << std::endl;
    }

    if (!ret) {
        throw std::runtime_error("can't load gltf scene");
    }

    // Use the default scene
    const tinygltf::Scene &scene = mModel.scenes[mModel.defaultScene];

    std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> vbos;
    for (int node : scene.nodes) {
        bindModelNodes(vbos, mModel, mModel.nodes[node]);
    }



}

void GLScene::SceneGLTF::render(std::shared_ptr<GLTools::Program> program, GLTools::RenderStep renderStep) const {

    // todo
}

float GLScene::SceneGLTF::getBoundingBoxDiagonal() {
    return 0;
}

void GLScene::SceneGLTF::bindModelNodes(std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> vbos, tinygltf::Model &model, tinygltf::Node &node) {
    bindMesh(vbos, model, model.meshes[node.mesh]);
    for (size_t i = 0; i < node.children.size(); i++) {
        bindModelNodes(vbos, model, model.nodes[node.children[i]]);
    }
}

std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> GLScene::SceneGLTF::bindMesh(std::map<std::shared_ptr<GLTools::ArrayBuffer>, GLuint> vbos, tinygltf::Model &model, tinygltf::Mesh &mesh) {
    for (size_t i = 0; i < model.bufferViews.size(); ++i) {
        const tinygltf::BufferView &bufferView = model.bufferViews[i];
        if (bufferView.target == 0) {  // TODO impl drawarrays
            std::cout << "WARN: bufferView.target is zero" << std::endl;
            continue;  // Unsupported bufferView.
            /*
              From spec2.0 readme:
              https://github.com/KhronosGroup/glTF/tree/master/specification/2.0
                       ... drawArrays function should be used with a count equal to
              the count            property of any of the accessors referenced by the
              attributes            property            (they are all equal for a given
              primitive).
            */
        }

        tinygltf::Buffer buffer = model.buffers[bufferView.buffer];
        std::cout << "bufferview.target " << bufferView.target << std::endl;


        switch (bufferView.target) {
            case GL_ARRAY_BUFFER:
                // todo;
            case GL_ELEMENT_ARRAY_BUFFER:
                // todo;
            default:
                break; // todo
        }
/*
        GLuint vbo;
        glGenBuffers(1, &vbo);
        vbos[i] = vbo;
        glBindBuffer(bufferView.target, vbo);

        std::cout << "buffer.data.size = " << buffer.data.size()
                  << ", bufferview.byteOffset = " << bufferView.byteOffset
                  << std::endl;

        glBufferData(bufferView.target, bufferView.byteLength,
                     &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);

    */
    }
/*
    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];
        tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

        for (auto &attrib : primitive.attributes) {
            tinygltf::Accessor accessor = model.accessors[attrib.second];
            int byteStride =
                    accessor.ByteStride(model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int vaa = -1;
            if (attrib.first.compare("POSITION") == 0) vaa = 0;
            if (attrib.first.compare("NORMAL") == 0) vaa = 1;
            if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
            if (vaa > -1) {
                glEnableVertexAttribArray(vaa);
                glVertexAttribPointer(vaa, size, accessor.componentType,
                                      accessor.normalized ? GL_TRUE : GL_FALSE,
                                      byteStride, BUFFER_OFFSET(accessor.byteOffset));
            } else
                std::cout << "vaa missing: " << attrib.first << std::endl;
        }

        GLuint texid;
        glGenTextures(1, &texid);

        tinygltf::Texture &tex = model.textures[0];
        tinygltf::Image &image = model.images[tex.source];

        glBindTexture(GL_TEXTURE_2D, texid);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        GLenum format = GL_RGBA;

        if (image.component == 1) {
            format = GL_RED;
        } else if (image.component == 2) {
            format = GL_RG;
        } else if (image.component == 3) {
            format = GL_RGB;
        } else {
            // ???
        }

        GLenum type = GL_UNSIGNED_BYTE;
        if (image.bits == 8) {
            // ok
        } else if (image.bits == 16) {
            type = GL_UNSIGNED_SHORT;
        } else {
            // ???
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, format, type, &image.image.at(0));
    }
*/
    return vbos;
}

