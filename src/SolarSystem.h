//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include <list>
#include <glm/ext.hpp>

#include "gltools/Window"
#include "astronomy/Astre"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void render() override;

    glm::vec3 translationScale(glm::vec3 translation);
    float radiusScale(float radius);

private:
    void add(std::shared_ptr<Astronomy::Astre> astre);

    GLTools::Camera mCamera;
    std::list<std::pair<std::shared_ptr<Astronomy::Astre>, std::shared_ptr<GLTools::Drawable>>> mAstresDrawable;

};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
