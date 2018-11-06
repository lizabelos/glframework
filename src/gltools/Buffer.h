//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_BUFFER_H
#define SOLAR_SYSTEM_BUFFER_H

#include <vector>
#include <map>
#include <memory>
#include <glm/ext.hpp>
#include <GL/glew.h>

namespace GLTools {

    class ArrayBuffer {

    public:
        explicit ArrayBuffer(std::vector<glm::vec2> vector);
        explicit ArrayBuffer(std::vector<glm::vec3> vector);
        ~ArrayBuffer();

        void bind();
        unsigned long getStep();
        unsigned long getSize();

    private:
        GLuint mId;
        unsigned long mStep;
        unsigned long mSize;

    };

    class ElementArrayBuffer {

    public:
        explicit ElementArrayBuffer(std::vector<uint32_t> vector);
        ~ElementArrayBuffer();

        void bind();
        unsigned long getStep();
        unsigned long getSize();

    private:
        GLuint mId;
        unsigned long mStep;
        unsigned long mSize;

    };

    class VertexArrayObject {

    public:
        VertexArrayObject();

        void add(GLuint id, std::shared_ptr<ArrayBuffer> buffer);
        void set(std::shared_ptr<ArrayBuffer> elementBuffer);
        void bind();

    private:
        GLuint mId;
        std::map<GLuint, std::shared_ptr<ArrayBuffer>> mBuffers;
        std::shared_ptr<ArrayBuffer> mElementBuffer;

    };

}


#endif //SOLAR_SYSTEM_BUFFER_H
