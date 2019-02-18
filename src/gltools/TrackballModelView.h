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
    class TrackballModelView : public ModelView3D {

    public:
        /**
         * Default construction for TrackballCamera. Intialize left and up with 0, and front with 50.
         */
        TrackballModelView();

        /**
         * Construct TrackballCamera with custom front, left and up orientation.
         * @param front Front distance to the center
         * @param left Left angle
         * @param up Up angle
         */
        TrackballModelView(float front, float left, float up);

        /**
         * @return The view matrix
         */
        glm::mat4 getViewMatrix() const;

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

        /**
         * Disable the translation
         */
         void enableTranslation() override;

         /**
          * Enable the translation
          */
         void disableTranslation() override;

    private:
        float mFront;
        float mLeft;
        float mUp;
        bool mTranslate;


    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
