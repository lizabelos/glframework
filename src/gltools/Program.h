//
// Created by thomas on 06/11/18.
//

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

namespace GLTools {
    class Program {

    public:
        Program(const std::string &vertexPath, const std::string &fragmentPath);
        Program(std::shared_ptr<Shader> pVertex, std::shared_ptr<Shader> pFragment);
        ~Program();

        void use() const;
        void post(const std::string &name, int number);
        void post(const std::string &name, const glm::mat4 &mat);
        void postTexture(const std::string &name, GLint texture);

        template<typename vecType> inline void post(const Camera<vecType> &camera) {
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
