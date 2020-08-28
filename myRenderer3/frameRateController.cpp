#include "frameRateController.h"
#include <Windows.h>
#include "engine.h"
#include <stdio.h>
#include "runMainLoop.h"

//LARGE_INTEGER nStopTime;


//void StartTimer(TimerHandle*);
//void StopTimer(TimerHandle*);
//float GetTimerElapsedMs((TimerHandle*);
//float GetTimerElapsedSeconds((TimerHandle*);

void frameStart(LARGE_INTEGER * nFrequency, LARGE_INTEGER * nStartTime)
{
    QueryPerformanceFrequency(nFrequency); //to be called only once. not per frame
    
    QueryPerformanceCounter(nStartTime);
}

void frameEnd(LARGE_INTEGER * nStopTime)
{
    // get new elapsed time
    // if (new elapsed time - start
    QueryPerformanceCounter(nStopTime);
}

bool isWithinFrameRate(LARGE_INTEGER *nStopTime, LARGE_INTEGER * nStartTime, LARGE_INTEGER * nFrequency, LARGE_INTEGER * defaultFrameTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart) * 1000000;
    nStopTime->QuadPart /= nFrequency->QuadPart;
    if (nStopTime->QuadPart > defaultFrameTime->QuadPart) {
        printf("%.2f\n", (float)nStopTime->QuadPart / 1000);
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
//float GetTimerElapsedMs(LARGE_INTEGER * nStartTime, LARGE_INTEGER *nStopTime, LARGE_INTEGER *nFrequency)
//float GetTimerElapsedMs()

//float GetTimerElapsedSeconds((TimerHandle*);
