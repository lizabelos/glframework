//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_LIGHTVIEW_H
#define BELOSGL_LIGHTVIEW_H

#include "View"

namespace GLTools {

    class LightView : public View {

    public:
        /**
         * Create a LightView
         */
        LightView();

        /**
         * Create a LightView
         */
        LightView(glm::vec3 sceneCenter, float sceneRadius, float phi, float theta, glm::vec3 direction);

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
         *
         * @return The light position
         */
        glm::vec3 getLightPosition() const;

    protected:
        void processLightMatrix();

    private:
        glm::mat4 mLightMatrix;
        glm::vec3 mLightPosition;
        float mSceneRadius;
        float mPhi;
        float mTheta;
        glm::vec3 mDirection;

    };

}


#endif //BELOSGL_LIGHTVIEW_H
