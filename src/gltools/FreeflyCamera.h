//
// Created by thomas on 07/12/18.
//

#ifndef SOLAR_SYSTEM_FREEFLYCAMERA_H
#define SOLAR_SYSTEM_FREEFLYCAMERA_H


#include <glm/ext.hpp>
#include <vector>

#include "Camera"

namespace GLTools {

    class FreeflyCamera : public Camera3D {

    public:
        FreeflyCamera();

        glm::mat4 getViewMatrix() const;
        glm::mat4 getMVMatrix() const override;
        glm::mat4 getNormalMatrix() const override;

        void moveLeft(float t);
        void moveFront(float t);

        void rotateLeft(float t);
        void rotateUp(float t);

        void setLeftRotation(float t);
        void setUpRotation(float t);

    protected:
        void computeDirectionVectors();

    private:
        glm::vec3 mPosition;
        float mPhi, mTheta;
        glm::vec3 mFront, mLeft, mUp;

    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
