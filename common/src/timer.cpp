#include <timer.h>
#include <common/timer.h>


//
// Created by Esdeath on 06/11/2018.
//

Timer::Timer() {
    init();
}

time_point<high_resolution_clock> Timer::getTime() {
    lastTimePoint = high_resolution_clock::now();
    return lastTimePoint;
}

time_point<high_resolution_clock> Timer::getCurrentTime() {
    return high_resolution_clock::now();
}

time_point<high_resolution_clock> Timer::getLastTimeCall() {
    return lastTimePoint;
}

double Timer::getElapsedTime() {
    auto currentTime = high_resolution_clock::now();
    elapsedTime = duration_cast<duration<double>>(currentTime - lastTimePoint);
    lastTimePoint = currentTime;
    return elapsedTime.count();
}

double Timer::getLastElapsedTime() {
    return elapsedTime.count();
}

double Timer::getFps() {
    return 1 / elapsedTime.count();
}

void Timer::init() {
    lastTimePoint = high_resolution_clock::now();
}
