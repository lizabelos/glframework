// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_PROGRAM_H
#define SOLAR_SYSTEM_PROGRAM_H

#define VERTEX_ID 0
#define NORMAL_ID 1
#define TEXTCOORD_ID 2

#include <memory>
#include <string>
#include <map>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/ext.hpp>

#include "Shader"
#include "Camera"

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * Permits to create OpenGL program from shaders, and to post any kind of values on it !
     */
    class Program {

    public:
        /**
         * Create one vertex shader, one fragment shader, and a fragment from these two
         * @param vertexPath The path on the vertex source code
         * @param fragmentPath The path on the fragment source code
         */
        Program(const std::string &vertexPath, const std::string &fragmentPath);

        /**
         * Create a program from one vertex shader, and one fragment shader
         * @param pVertex The vertex shader
         * @param pFragment The fragment shader
         */
        Program(std::shared_ptr<Shader> pVertex, std::shared_ptr<Shader> pFragment);

        /**
         * The destructor is virtual.
         */
        virtual ~Program();

        /**
         * Use this shader.
         */
        void use() const;

        /**
         * Post a uniform integer to the shader
         * @param name Name of the uniform
         * @param number Value to pass
         */
        void post(const std::string &name, int number);

        /**
         * Post a uniform float to the shader
         * @param name Name of the uniform
         * @param number Value to pass
         */
        void post(const std::string &name, float number);

        /**
         * Post a uniform mat4 to the shader
         * @param name Name of the uniform
         * @param mat Value to pass
         */
        void post(const std::string &name, const glm::mat4 &mat);

        /**
         * Post a uniform vec4 to the shader
         * @param name Name of the uniform
         * @param mat Value to pass
         */
        void post(const std::string &name, const glm::vec4 &mat);

        /**
         * Post a uniform texture to the shader
         * @param name The Name of the uniform
         * @param texture The texture unit id
         */
        void postTexture(const std::string &name, GLint texture);

        /**
         * Post the information of the camera.
         * Same as post(uMVPMatrix", camera.getProjectionMatrix() * camera.getMVMatrix());
         * @tparam vecType Either 2D or 3D
         * @param camera The camera to post
         */
        template<typename vecType> inline void post(const Camera<vecType> &camera) {
            post("uModelMatrix", camera.getModelMatrix());
            post("uMVPMatrix", camera.getProjectionMatrix() * camera.getMVMatrix());
        }

    protected:
        void uniform(const std::string &name);

    private:
        void initialize();

        GLuint mId;
        std::shared_ptr<Shader> mVertex;
        std::shared_ptr<Shader> mFragment;
        std::map<std::string, GLint> mUniformMap;

    };
}


#endif //SOLAR_SYSTEM_PROGRAM_H
