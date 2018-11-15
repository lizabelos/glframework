//
// Created by thomas on 06/11/18.
//

#include "Shader.h"

#include <iostream>
#include <fstream>

GLTools::Shader::Shader(GLenum type, const std::string &path) {

    mType = type;

    mId = glCreateShader(mType);
    if (mId == 0) {
        throw std::runtime_error("glCreateShader failed");
    }

    if (glIsShader(mId) != GL_TRUE) {
        throw std::runtime_error("glIsShader failed");
    }

    std::ifstream file(path.c_str());
    if (!file) {
        throw std::runtime_error("Can't open '" + path + "'");
    }

    // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::string fileContent;
    file.seekg(0, std::ios::end);
    fileContent.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);
    fileContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    //

    const GLchar *fileContentC = fileContent.c_str();
    glShaderSource(mId, 1, &fileContentC, nullptr);


    std::cout << "Compiling shader '" << path << "' with id " << mId << "." << std::endl;
    glCompileShader(mId);

    GLint error = 0;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &error);


    GLint errorSize = 0;
    glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &errorSize);

    char *errorStr = new char[errorSize + 1];
    glGetShaderInfoLog(mId, errorSize, &errorSize, errorStr);
    errorStr[errorSize] = '\0';

    std::cerr << errorStr << std::endl;

    if (error != GL_TRUE) {
        delete[] errorStr;
        exit(EXIT_FAILURE);

    }


}

GLTools::Shader::~Shader() {
    glDeleteShader(mId);
}

GLuint GLTools::Shader::getId() {
    return mId;
}
