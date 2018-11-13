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

        glm::mat4 getProjectionMatrix();
        glm::mat4 getMVMatrix();
        glm::mat4 getNormalMatrix();

        void pushMVMatrix();
        void popMVMatrix();
        void mulMVMatrix(glm::mat4 matrix);

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mMVMatrix;
        glm::mat4 mNormalMatrix;

        std::vector<glm::mat4> mMVMatrixStack;

    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
