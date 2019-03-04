//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_LIGHTVIEW_H
#define BELOSGL_LIGHTVIEW_H

#include <vector>

#include "View"

namespace GLTools {

    class LightView {

    public:
        /**
         * Create a LightView
         */
        LightView();

        /**
         * Create a LightView
         */
        LightView(glm::vec3 lightPosition);

        /**
         * @return The view matrix
         */
        std::vector<glm::mat4> getMatrices() const;

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
        std::vector<glm::mat4> mLightMatrices;
        glm::vec3 mLightPosition;
    };

}


#endif //BELOSGL_LIGHTVIEW_H
