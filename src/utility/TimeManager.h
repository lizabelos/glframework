//
// Created by thomas on 13/01/19.
//

#ifndef SOLAR_SYSTEM_TIMEMANAGER_H
#define SOLAR_SYSTEM_TIMEMANAGER_H

#include <chrono>

class TimeManager {

public:
    TimeManager();

    float getTime();

    void pause();
    void play();
    void pauseplay();

    void speedup();
    void seepdown();

private:
    bool mPlay;
    float mSpeed;
    float mCurrent;
    std::chrono::steady_clock::time_point mStart;

};


#endif //SOLAR_SYSTEM_TIMEMANAGER_H
