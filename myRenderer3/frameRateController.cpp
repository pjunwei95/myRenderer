#include "frameRateController.h"
#include "engine.h"

Timer nFrequency;
Timer defaultFrameTime;

void initialiseTimer()
{
    // 1s = 1 000 000 micro s = 30 frames
    defaultFrameTime.QuadPart = 1000000 / FPS; // unit is in seconds, NOT microseconds

    QueryPerformanceFrequency(&nFrequency); //to be called only once. not per frame
}

bool isWithinFrameRate(TimerHandle nStartTime, TimerHandle nStopTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart); //the units here are in seconds
    nStopTime->QuadPart *= 1000000; //convert seconds to microseconds
    nStopTime->QuadPart /= nFrequency.QuadPart;
    if (nStopTime->QuadPart > defaultFrameTime.QuadPart) {
        return true;
    }
    return false;
}

void startTimer(TimerHandle nStartTime)
{
    QueryPerformanceCounter(nStartTime);
}

void stopTimer(TimerHandle nStopTime)
{
    QueryPerformanceCounter(nStopTime);
}

float getTimerElapsedMs(const TimerHandle nStopTime)
{
    return (float) nStopTime->QuadPart / 1000;
}

float getTimerElapsedSeconds(const TimerHandle nStopTime)
{
    return (float)nStopTime->QuadPart / 1000000;
}