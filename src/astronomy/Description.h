// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_DESCRIPTION_H
#define SOLAR_SYSTEM_DESCRIPTION_H


namespace Astronomy {

    typedef struct description_t {
        double diameter;
        double rotationPeriod;
        double sunDistance;
        double orbitalPeriod;
        double orbitalVelocity;
        double orbitalInclination;
        double orbitalEccentricity;
        int moonNumber;
        bool ringSystem;
    } description_t;

}


#endif //SOLAR_SYSTEM_DESCRIPTION_H
