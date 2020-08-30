#include "frameRateController.h"
#include <Windows.h>
#include "engine.h"
#include <stdio.h>
#include "runMainLoop.h"

//void StartTimer(TimerHandle*);
//void StopTimer(TimerHandle*);
//float GetTimerElapsedMs((TimerHandle*);
//float GetTimerElapsedSeconds((TimerHandle*);


bool isWithinFrameRate(LARGE_INTEGER *nStartTime, LARGE_INTEGER * nStopTime, LARGE_INTEGER * nFrequency, LARGE_INTEGER * defaultFrameTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart); //the units here are in seconds
    nStopTime->QuadPart *= 1000000; //convert seconds to microseconds
    nStopTime->QuadPart /= nFrequency->QuadPart;
    if (nStopTime->QuadPart > defaultFrameTime->QuadPart) {
        return true;
    }
    return false;
}

void StartTimer(LARGE_INTEGER *nStartTime)
{
    QueryPerformanceCounter(nStartTime);
}
void StopTimer(LARGE_INTEGER *nStopTime)
{
    QueryPerformanceCounter(nStopTime);
}

float GetTimerElapsedMs(LARGE_INTEGER* nStopTime)
{
    return (float) nStopTime->QuadPart / 1000;
}

float GetTimerElapsedSeconds(LARGE_INTEGER* nStopTime)
{
    return (float)nStopTime->QuadPart / 1000000;
}