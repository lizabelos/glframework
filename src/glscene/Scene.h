//
// Created by thomas on 13/03/19.
//

#ifndef BELOSGL_SCENE_H
#define BELOSGL_SCENE_H

#include "../gltools/Drawable"

namespace GLScene {


    class Scene : public GLTools::Drawable<glm::vec3> {

    public:
        Scene(int id);

        virtual float getBoundingBoxDiagonal() = 0;


    };

}


#endif //BELOSGL_SCENE_H
