// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_BUFFER_H
#define SOLAR_SYSTEM_BUFFER_H

#include <vector>
#include <map>
#include <memory>
#include <glm/ext.hpp>
#include <GL/glew.h>

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * OpenGL ArrayBuffer wrapper
     */
    class ArrayBuffer {

    public:
        /**
         * You can't use the default constructor
         */
        ArrayBuffer() = delete;

        /**
         * Create an array buffer from a 2D vector
         * @param vector The vector to send to the video memory
         * @param staticDraw True if no update will be done on the array (faster)
         */
        explicit ArrayBuffer(std::vector<glm::vec2> vector, bool staticDraw = true);

        /**
         * Create an array buffer from a 2D vector
         * @param vector The vector to send to the video memory
         * @param staticDraw True if no update will be done on the array (faster)
         */
        explicit ArrayBuffer(std::vector<glm::vec3> vector, bool staticDraw = true);

        /**
         * Destruct the array buffer from the video memory
         */
        ~ArrayBuffer();

        /**
         * You can't copy an ArrayBuffer.
         */
        ArrayBuffer( const ArrayBuffer& ) = delete;
        ArrayBuffer& operator=( const ArrayBuffer& ) = delete;

        /**
         * Bind this buffer
         */
        void bind() const;

        /**
         * @return the dimension of the buffer
         */
        unsigned long getStep() const;

        /**
         * @return the size of the buffer
         */
        unsigned long getSize() const;

        /**
         * Update an array buffer from a 2D vector
         * @param vector The vector to send to the video memory
         */
        void update(std::vector<glm::vec2> vector);

        /**
         * Update an array buffer from a 3D vector
         * @param vector The vector to send to the video memory
         */
        void update(std::vector<glm::vec3> vector);

    private:
        GLuint mId;
        unsigned long mStep;
        unsigned long mSize;

    };

    /**
     * OpenGL ElementArrayBuffer wrapper
     */
    class ElementArrayBuffer {

    public:
        /**
         * You can't use the default constructor
         */
        ElementArrayBuffer() = delete;

        /**
         * Create an array buffer from an integer vector
         * @param vector The vector to send to the video memory
         * @param staticDraw True if no update will be done on the array (faster)
         */
        explicit ElementArrayBuffer(std::vector<uint32_t> vector, bool staticDraw = true);

        /**
         * Destruct the element array buffer from the video memory
         */
        ~ElementArrayBuffer();

        /**
         * You can't copy an ElementArrayBuffer.
         */
        ElementArrayBuffer( const ElementArrayBuffer& ) = delete;
        ElementArrayBuffer& operator=( const ElementArrayBuffer& ) = delete;

        /**
         * Bind this buffer
         */
        void bind() const;

        /**
         * @return the dimension of the buffer
         */
        unsigned long getStep() const;

        /**
         * @return the size of the buffer
         */
        unsigned long getSize() const;

        /**
         * Update an array buffer from a index vector
         * @param vector The vector to send to the video memory
         */
        void update(std::vector<uint32_t> vector);

    private:
        GLuint mId;
        unsigned long mStep;
        unsigned long mSize;

    };

    /**
     * An OpenGL VAO Wrapper
     */
    class VertexArrayObject {

    public:
        /**
         * Default constructor
         */
        VertexArrayObject();

        /**
         * Link an ArrayBuffer to this VAO
         * @param id The id of the buffer used in the shader
         * @param buffer A shared pointer to the ArrayBuffer
         */
        void add(GLuint id, std::shared_ptr<ArrayBuffer> buffer);

        /**
         * Set the ElementArrayBuffer of this VAO
         * @param elementBuffer A shared pointer to the ElementArrayBuffer
         */
        void set(std::shared_ptr<ElementArrayBuffer> elementBuffer);

        /**
         * Bind this VAO
         */
        void bind() const;

    private:
        GLuint mId;
        std::map<GLuint, std::shared_ptr<ArrayBuffer>> mBuffers;
        std::shared_ptr<ElementArrayBuffer> mElementBuffer;

    };

}


#endif //SOLAR_SYSTEM_BUFFER_H
