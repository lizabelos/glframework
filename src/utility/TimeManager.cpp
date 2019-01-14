//
// Created by thomas on 13/01/19.
//

#include "TimeManager.h"

TimeManager::TimeManager() {
    mPlay = true;
    mSpeed = 1.0f;
    mCurrent = 0.0f;
    mStart = std::chrono::steady_clock::now();

}

float TimeManager::getTime() {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    if (mPlay) mCurrent += (float)std::chrono::duration_cast<std::chrono::microseconds>(end - mStart).count() * 1e-6f * mSpeed;
    mStart = end;
    return mCurrent;
}

void TimeManager::pause() {
    mPlay = false;
}

void TimeManager::play() {
    mPlay = true;
}

void TimeManager::pauseplay() {
    mPlay = !mPlay;
}

void TimeManager::speedup() {
    mSpeed = mSpeed * 2.0f;
}

void TimeManager::seepdown() {
    mSpeed = mSpeed * 0.5f;
}



