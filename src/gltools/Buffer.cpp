//
// Created by thomas on 06/11/18.
//

#include "Buffer.h"

GLTools::ArrayBuffer::ArrayBuffer(std::vector<glm::vec2> vector) {
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vector.size(), static_cast<void*>(vector.data()), GL_STATIC_DRAW);
    mStep = 2;
    mSize = vector.size();
}

GLTools::ArrayBuffer::ArrayBuffer(std::vector<glm::vec3> vector) {
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vector.size(), static_cast<void*>(vector.data()), GL_STATIC_DRAW);
    mStep = 3;
    mSize = vector.size();
}

GLTools::ArrayBuffer::~ArrayBuffer() {
    glDeleteBuffers(1, &mId);
}

void GLTools::ArrayBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mId);
}

unsigned long GLTools::ArrayBuffer::getStep() const {
    return mStep;
}

unsigned long GLTools::ArrayBuffer::getSize() const {
    return mSize;
}

GLTools::ElementArrayBuffer::ElementArrayBuffer(std::vector<uint32_t> vector) {
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * vector.size(), static_cast<void*>(vector.data()), GL_STATIC_DRAW);
    mStep = 1;
    mSize = vector.size();
}

GLTools::ElementArrayBuffer::~ElementArrayBuffer() {
    glDeleteBuffers(1, &mId);
}

void GLTools::ElementArrayBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
}

unsigned long GLTools::ElementArrayBuffer::getStep() const {
    return mStep;
}

unsigned long GLTools::ElementArrayBuffer::getSize() const {
    return mSize;
}

GLTools::VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &mId);
}

void GLTools::VertexArrayObject::bind() const {
    glBindVertexArray(mId);
    if (mElementBuffer != nullptr) mElementBuffer->bind();
}

void GLTools::VertexArrayObject::add(GLuint id, std::shared_ptr<GLTools::ArrayBuffer> buffer) {
    mBuffers[id] = buffer;
    bind();
    buffer->bind();
    glVertexAttribPointer(id, static_cast<GLint>(buffer->getStep()), GL_FLOAT, GL_FALSE, static_cast<GLsizei>(buffer->getStep() * sizeof(float)), 0);
}

void GLTools::VertexArrayObject::set(std::shared_ptr<GLTools::ArrayBuffer> elementBuffer) {
    mElementBuffer = elementBuffer;
    bind();
    elementBuffer->bind();
}
