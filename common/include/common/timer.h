//
// Created by Esdeath on 06/11/2018.
//

#ifndef FONG_TIMER_H
#define FONG_TIMER_H

#include <chrono>
using namespace std::chrono;

class Timer {
public:
    Timer();
    ~Timer() = default;

    time_point<high_resolution_clock> getCurrentTime();
    time_point<high_resolution_clock> getTime();
    time_point<high_resolution_clock> getLastTimeCall();
    double getElapsedTime();
    double getLastElapsedTime();
    double getFps();
private:
    void init();

    time_point<high_resolution_clock> lastTimePoint;
    duration<double> elapsedTime;
};

#endif //FONG_TIMER_H
