//
// Created by thomas on 07/12/18.
//

#ifndef SOLAR_SYSTEM_FREEFLYCAMERA_H
#define SOLAR_SYSTEM_FREEFLYCAMERA_H


#include <glm/ext.hpp>
#include <vector>

#include "Camera"

/**
 * A namespace regrouping all the GLTools OpenGL wrapper.
 */
namespace GLTools {

    /**
     * A FreeflyCamera 3D Camera
     */
    class FreeflyCamera : public Camera3D {

    public:
        /**
         * Default constructor to FreeflyCamera. Initialize each angles to zeros.
         */
        FreeflyCamera();

        /**
         * @return The view matrix
         */
        glm::mat4 getViewMatrix() const;

        /**
         * Move left
         * @param t The factor to add
         */
        void moveLeft(float t);

        /**
         * Move front
         * @param t The factor to add
         */
        void moveFront(float t);

        /**
         * Move up
         * @param t The factor to add
         */
        void moveUp(float t);

        /**
         * Rotate left
         * @param t The angle to add
         */
        void rotateLeft(float t);

        /**
         * Rotate up
         * @param t The angle to add
         */
        void rotateUp(float t);

        /**
         * Disable the translation
         */
        void enableTranslation() override;

        /**
         * Enable the translation
         */
        void disableTranslation() override;

        glm::vec3 getPosition() override;

    private:
        glm::vec3 mPosition;
        float mPitch, mRoll, mYaw;
        bool mTranslate;

    };

}


#endif //SOLAR_SYSTEM_CAMERA_H
