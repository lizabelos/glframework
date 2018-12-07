//
// Created by thomas on 07/12/18.
//

#ifndef SOLAR_SYSTEM_TRACKBALLCAMERA_H
#define SOLAR_SYSTEM_TRACKBALLCAMERA_H


#include <glm/ext.hpp>
#include <vector>

#include "Camera"

namespace GLTools {

    class TrackballCamera : public Camera3D {

    public:
        TrackballCamera();
        TrackballCamera(float front, float left, float up);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getMVMatrix() const override;
        glm::mat4 getNormalMatrix() const override;

        void moveFront(float delta);
        void rotateLeft(float delta);
        void rotateUp(float delata);

    private:
        float mFront;
        float mLeft;
        float mUp;


    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
