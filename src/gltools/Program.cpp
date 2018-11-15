//
// Created by thomas on 06/11/18.
//

#include "Program.h"
#include <iostream>

GLTools::Program::Program(std::shared_ptr<GLTools::Shader> pVertex, std::shared_ptr<GLTools::Shader> pFragment) {

    mVertex = pVertex;
    mFragment = pFragment;
    initialize();

}

GLTools::Program::Program(const std::string &vertexPath, const std::string &fragmentPath) {

    mVertex = std::shared_ptr<Shader>(new Shader(GL_VERTEX_SHADER, vertexPath));
    mFragment = std::shared_ptr<Shader>(new Shader(GL_FRAGMENT_SHADER, fragmentPath));
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

void GLTools::Program::post(const std::string &name, const glm::mat4 &mat) {
    uniform(name);
    glUniformMatrix4fv(mUniformMap[name], 1, GL_FALSE, glm::value_ptr(mat));
}

void GLTools::Program::post(const GLTools::Camera &camera) {
    post("uMVPMatrix", camera.getProjectionMatrix() * camera.getMVMatrix());
}

void GLTools::Program::uniform(const std::string &name) {
    if (mUniformMap.count(name) == 0) {
        mUniformMap[name] = glGetUniformLocation(mId, name.c_str());
        std::cout << "The uniform of program " << mId << " with name " << name << " is " << mUniformMap[name] << std::endl;
    }
}

