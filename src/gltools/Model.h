// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef BELOSGL_MODEL_H
#define BELOSGL_MODEL_H

#include <vector>
#include <glm/ext.hpp>

namespace GLTools {

    class Model2D {

    public:
        /**
         * Constructor for Model2D
         */
         Model2D();

        /**
         * @return The model matrix
         */
        glm::mat3 getMatrix() const;

        /**
        * Push the current MV Matrix to the stack
        */
        void pushMatrix();

        /**
         * Pop the current MV Matrix from the stack
         */
        void popMatrix();

        /**
         * Translate the camera
         * @param translation The translation vector
         */
        void translate(glm::vec2 translation);

        /**
         * Rotate the camera
         * @param angle The rotation angle
         * @param axis The rotation axis for 3D
         */
        void rotate(float angle);

        /**
         * Scale the camera
         * @param scaling The scaling vector
         */
        void scale(glm::vec2 scaling);

        /**
         * Scale the camera along all the axis
         * @param scaling The scaling coefficient
         */
        void scale(float scaling);

        /**
         * Load the identity matrix
         */
        void identity();

    private:
        glm::mat3 mModelMatrix;
        std::vector<glm::mat3> mMVMatrixStack;

    };

    class Model3D {

    public:
        /**
         * Constructor for Model2D
         */
        Model3D();

        /**
         * @return The model matrix
         */
        glm::mat4 getMatrix() const;

        /**
        * Push the current MV Matrix to the stack
        */
        void pushMatrix();

        /**
         * Pop the current MV Matrix from the stack
         */
        void popMatrix();

        /**
         * Translate the camera
         * @param translation The translation vector
         */
        void translate(glm::vec3 translation);

        /**
         * Rotate the camera
         * @param angle The rotation angle
         * @param axis The rotation axis for 3D
         */
        void rotate(float angle, glm::vec3 axis);

        /**
         * Scale the camera
         * @param scaling The scaling vector
         */
        void scale(glm::vec3 scaling);

        /**
         * Scale the camera along all the axis
         * @param scaling The scaling coefficient
         */
        void scale(float scaling);

        /**
         * Load the identity matrix
         */
        void identity();

    private:
        glm::mat4 mModelMatrix;
        std::vector<glm::mat4> mMVMatrixStack;


    };

}


#endif //BELOSGL_MODEL_H
