#include <memory>

//
// Created by thomas on 06/11/18.
//

#include "Program.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

GLTools::Program::Program(std::shared_ptr<GLTools::Shader> pVertex, std::shared_ptr<GLTools::Shader> pFragment) {

    mVertex = pVertex;
    mFragment = pFragment;
    initialize();

}

GLTools::Program::Program(const std::string &vertexPath, const std::string &fragmentPath) {

    mVertex = std::make_shared<Shader>(GL_VERTEX_SHADER, vertexPath);
    mFragment = std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragmentPath);
    initialize();

}


void GLTools::Program::initialize() {

    mId = glCreateProgram();

    std::cout << "Creating a new program " << mId << " with vertex shader " << mVertex->getId() << " and fragment shader " << mFragment->getId() << std::endl;

    glAttachShader(mId, mVertex->getId());
    glAttachShader(mId, mFragment->getId());

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

void GLTools::Program::post(const std::string &name, int number) {
    uniform(name);
    use();
    glUniform1i(mUniformMap[name], number);
}

void GLTools::Program::post(const std::string &name, bool value) {
    uniform(name);
    use();
    glUniform1i(mUniformMap[name], value);
}

void GLTools::Program::post(const std::string &name, float number) {
    uniform(name);
    use();
    glUniform1f(mUniformMap[name], number);
}

void GLTools::Program::post(const std::string &name, const glm::mat4 &mat) {
    uniform(name);
    use();
    glUniformMatrix4fv(mUniformMap[name], 1, GL_FALSE, glm::value_ptr(mat));
}

void GLTools::Program::post(const std::string &name, const glm::vec4 &mat) {
    uniform(name);
    use();
    glUniform4fv(mUniformMap[name], 1, glm::value_ptr(mat));
}

void GLTools::Program::post(const std::string &name, const glm::mat3 &mat) {
    uniform(name);
    use();
    glUniformMatrix3fv(mUniformMap[name], 1, GL_FALSE, glm::value_ptr(mat));
}

void GLTools::Program::post(const std::string &name, const glm::vec3 &mat) {
    uniform(name);
    use();
    glUniform3fv(mUniformMap[name], 1, glm::value_ptr(mat));
}

void GLTools::Program::uniform(const std::string &name) {
    if (mUniformMap.count(name) == 0) {
        mUniformMap[name] = glGetUniformLocation(mId, name.c_str());
        std::cout << "The uniform of program " << mId << " with name " << name << " is " << mUniformMap[name] << std::endl;
    }
}

void GLTools::Program::postTexture(const std::string &name, GLint texture) {
    uniform(name);
    use();
    glUniform1i(mUniformMap[name], texture);
}
