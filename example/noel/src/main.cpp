#include <glscene/SceneASSIMP.h>
#include <algorithm>
#include <glscene/SceneGLTF.h>
#include <iostream>
#include "OpenglNoel.h"

int main(int argc, char **argv) {
    OpenglNoel openglNoel;

    std::string modelType;
    switch (argc) {
        case 1:
            openglNoel.useScene(std::make_shared<GLScene::SceneASSIMP>("res/objs/sponza"));
            break;
        case 2:
            openglNoel.useScene(std::make_shared<GLScene::SceneASSIMP>(argv[1]));
            break;
        case 3:
            modelType = argv[1];
            std::transform(modelType.begin(), modelType.end(),modelType.begin(), ::toupper);

            if (modelType == "ASSIMP") {

                openglNoel.useScene(std::make_shared<GLScene::SceneASSIMP>(argv[2]));

            } else if (modelType == "GLTF") {

                openglNoel.useScene(std::make_shared<GLScene::SceneGLTF>(argv[2]));

            } else {
                throw std::runtime_error("Unknown model type " + modelType);
            }
            break;
        default:
            std::cout << argv[0] << std::endl;
            std::cout << argv[0] << " [OBJ_MODEL]" << std::endl;
            std::cout << argv[0] << " [ASSIMP or GLTF] [MODEL]" << std::endl;
            break;
    }
    if (argc == 1) {
        openglNoel.useScene(std::make_shared<GLScene::SceneASSIMP>("res/objs/sponza"));
    }

    if (argc == 2) {

    }

    if (argc == 3) {

    }


    openglNoel.run();
}
