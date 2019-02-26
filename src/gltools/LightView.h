//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_LIGHTVIEW_H
#define BELOSGL_LIGHTVIEW_H

#include "View"

namespace GLTools {

    class LightView {

    public:
        /**
         * Create a FreeflyView
         */
        LightView();

        /**
         * @return The view matrix
         */
        glm::mat4 getMatrix() override;

    private:
        glm::mat4 lightMatrix;

    };

}


#endif //BELOSGL_LIGHTVIEW_H
