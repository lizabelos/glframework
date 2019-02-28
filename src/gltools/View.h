//
// Created by belos on 26/02/2019.
//

#ifndef BELOSGL_VIEW_H
#define BELOSGL_VIEW_H

#include <glm/ext.hpp>

namespace GLTools {

    class View {

    public:
        /**
         * @return The view matrix
         */
        virtual glm::mat4 getMatrix() const = 0;

    };

}


#endif //BELOSGL_VIEW_H
