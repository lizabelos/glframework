//
// Created by thomas on 06/11/18.
//

#include "Program.h"

GLTools::Program::Program(std::shared_ptr<GLTools::Shader> pVertex, std::shared_ptr<GLTools::Shader> pFragment) {

    mId = glCreateProgram();

    glAttachShader(mId, pVertex->getId());
    glAttachShader(mId, pFragment->getId());

    glLinkProgram(mId);

    GLint error = 0;
    glGetProgramiv(mId, GL_LINK_STATUS, &error);

    GLint errorSize = 0;
    glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &errorSize);

    char errorStr[errorSize + 1];
    glGetProgramInfoLog(mId, errorSize, &errorSize, errorStr);
    errorStr[errorSize] = '\0';

    if (error != GL_TRUE) {
        throw std::runtime_error("Program Error : " + std::string(errorStr));
    }

}

GLTools::Program::~Program() {
    glDeleteProgram(mId);
}

void GLTools::Program::use() const {
    glUseProgram(mId);
}

void GLTools::Program::post(const std::string &name, const glm::mat4 &mat) {
    uniform(name);
    glUniformMatrix4fv(mId, 1, GL_FALSE, glm::value_ptr(mat));
}

void GLTools::Program::uniform(const std::string &name) {
    if (mUniformMap.count(name) == 0) {
        mUniformMap[name] = glGetUniformLocation(mId, name.c_str());
    }
}

