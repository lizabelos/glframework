//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_PROGRAM_H
#define SOLAR_SYSTEM_PROGRAM_H

#include <memory>
#include <string>
#include <map>
#include <glm/ext.hpp>

#include "Shader"

namespace GLTools {
    class Program {

    public:
        Program(std::shared_ptr<Shader> pVertex, std::shared_ptr<Shader> pFragment);
        ~Program();

        void use() const;
        void post(const std::string &name, const glm::mat4 &mat);

    protected:
        void uniform(const std::string &name);

    private:
        GLuint mId;
        std::shared_ptr<Shader> mVertex;
        std::shared_ptr<Shader> mFragment;
        std::map<std::string, GLint> mUniformMap;

    };
}


#endif //SOLAR_SYSTEM_PROGRAM_H
