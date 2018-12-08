// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_TRACKBALLCAMERA_H
#define SOLAR_SYSTEM_TRACKBALLCAMERA_H


#include <glm/ext.hpp>
#include <vector>

#include "Camera"

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * A 3D Trackball camera
     * @see Camera3D
     */
    class TrackballCamera : public Camera3D {

    public:
        /**
         * Default construction for TrackballCamera. Intialize left and up with 0, and front with 50.
         */
        TrackballCamera();

        /**
         * Construct TrackballCamera with custom front, left and up orientation.
         * @param front Front distance to the center
         * @param left Left angle
         * @param up Up angle
         */
        TrackballCamera(float front, float left, float up);

        /**
         * @return The view matrix
         */
        glm::mat4 getViewMatrix() const;

        /**
         * @return The MV Matrix
         */
        glm::mat4 getMVMatrix() const override;

        /**
         * @return The normal matrix
         */
        glm::mat4 getNormalMatrix() const override;

        /**
         * Move front
         * @param delta Mouvement multiplicator
         */
        void moveFront(float delta);

        /**
         * Rotate left
         * @param delta Angle factor
         */
        void rotateLeft(float delta);

        /**
         * Rotate up
         * @param delta Angle factor
         */
        void rotateUp(float delta);

    private:
        float mFront;
        float mLeft;
        float mUp;


    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
