//
// Created by thomas on 13/11/18.
//

#ifndef SOLAR_SYSTEM_SOLARSYSTEM_H
#define SOLAR_SYSTEM_SOLARSYSTEM_H

#include "gltools/Window"

class SolarSystem : public GLTools::Window {

public:
    SolarSystem();

protected:
    void render() const override;

};


#endif //SOLAR_SYSTEM_SOLARSYSTEM_H
