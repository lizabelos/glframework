//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_FREEFLYVIEW_H
#define BELOSGL_FREEFLYVIEW_H

#include "View"

namespace GLTools {

    class FreeflyView : public View {

    public:

        /**
         * Create a FreeflyView
         */
        FreeflyView();

        /**
         * @return The view matrix
         */
        glm::mat4 getMatrix() const override;

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
         * @return The freefly camera position
         */
        glm::vec3 getPosition() const;

    private:
        glm::vec3 mPosition;
        float mPitch, mRoll, mYaw;

    };

}


#endif //BELOSGL_FREEFLYVIEW_H
