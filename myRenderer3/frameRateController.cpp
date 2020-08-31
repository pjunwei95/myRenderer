#include "frameRateController.h"

bool isWithinFrameRate(TimerHandle *nStartTime, TimerHandle * nStopTime, TimerHandle * nFrequency, TimerHandle * defaultFrameTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart); //the units here are in seconds
    nStopTime->QuadPart *= 1000000; //convert seconds to microseconds
    nStopTime->QuadPart /= nFrequency->QuadPart;
    if (nStopTime->QuadPart > defaultFrameTime->QuadPart) {
        return true;
    }
    return false;
}

void StartTimer(TimerHandle *nStartTime)
{
    QueryPerformanceCounter(nStartTime);
}

void StopTimer(TimerHandle *nStopTime)
{
    QueryPerformanceCounter(nStopTime);
}

float GetTimerElapsedMs(TimerHandle* nStopTime)
{
    return (float) nStopTime->QuadPart / 1000;
}

float GetTimerElapsedSeconds(TimerHandle* nStopTime)
{
    return (float)nStopTime->QuadPart / 1000000;
}