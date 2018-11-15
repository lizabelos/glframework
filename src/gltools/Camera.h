//
// Created by thomas on 06/11/18.
//

#ifndef SOLAR_SYSTEM_CAMERA_H
#define SOLAR_SYSTEM_CAMERA_H


#include <glm/ext.hpp>
#include <vector>

namespace GLTools {

    class Camera {

    public:
        Camera();

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getMVMatrix() const;
        glm::mat4 getNormalMatrix() const;

        void pushMatrix();
        void popMatrix();

        void translate(glm::vec3 translation);
        void rotate(glm::vec3 rotation);
        void scale(glm::vec3 scaling);
        void scale(float scaling);

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mMVMatrix;
        glm::mat4 mNormalMatrix;

        std::vector<glm::mat4> mMVMatrixStack;

    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
