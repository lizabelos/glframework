//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_TRACKBALLVIEW_H
#define BELOSGL_TRACKBALLVIEW_H

#include "View"

namespace GLTools {

    class TrackballView : public View {

    public:
        /**
         * Create a trackball view
         */
        TrackballView();

        /**
         * Create a track view with the given value
         * @param front The front value
         * @param left The left value
         * @param up The up value
         */
        TrackballView(float front, float left, float up);

        /**
         * @return The view matrix
         */
        glm::mat4 getMatrix() const override;

        /**
         * Move front
         * @param delta Mouvement multiplicator
         */
        void moveFront(float delta);
        void setFront(float front);

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
         * @return Return the camera position
         */
        glm::vec3 getPosition() const override;

    private:
        float mFront;
        float mLeft;
        float mUp;

    };

};


#endif //BELOSGL_TRACKBALLVIEW_H
