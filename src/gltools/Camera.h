//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_CAMERA_H
#define SOLAR_SYSTEM_CAMERA_H


#include <glm/ext.hpp>
#include <vector>

namespace GLTools {

    template<typename vecType> class Camera {

    public:
        virtual glm::mat4 getProjectionMatrix() const = 0;
        virtual glm::mat4 getMVMatrix() const = 0;
        virtual glm::mat4 getNormalMatrix() const = 0;

        virtual void pushMatrix() = 0;
        virtual void popMatrix() = 0;

        virtual void translate(vecType translation) = 0;
        virtual void rotate(float angle, vecType axis) = 0;
        virtual void scale(vecType scaling) = 0;
        virtual void scale(float scaling) = 0;

    };

    class Camera3D : public Camera<glm::vec3> {

    public:
        Camera3D();
        Camera3D(unsigned int width, unsigned int height);

        glm::mat4 getProjectionMatrix() const override;
        glm::mat4 getMVMatrix() const override;
        glm::mat4 getNormalMatrix() const override;

        void pushMatrix() override;
        void popMatrix() override;

        void translate(glm::vec3 translation) override;
        void rotate(float angle, glm::vec3 axis) override;
        void scale(glm::vec3 scaling) override;
        void scale(float scaling) override;

        void identity();
        void resize(unsigned int width, unsigned int height);

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mMVMatrix;

        std::vector<glm::mat4> mMVMatrixStack;

    };

    class Camera2D : public Camera<glm::vec2> {

    public:
        Camera2D();
        Camera2D(unsigned int width, unsigned int height);

        glm::mat4 getProjectionMatrix() const override;
        glm::mat4 getMVMatrix() const override;
        glm::mat4 getNormalMatrix() const override;

        void pushMatrix() override;
        void popMatrix() override;

        void translate(glm::vec2 translation) override;
        void rotate(float angle, glm::vec2 axis) override;
        void scale(glm::vec2 scaling) override;
        void scale(float scaling) override;

        void identity();
        void resize(unsigned int width, unsigned int height);

    private:
        glm::mat3 mProjectionMatrix;
        glm::mat3 mMVMatrix;

        glm::vec2 mWindowSize;

        std::vector<glm::mat3> mMVMatrixStack;

    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
