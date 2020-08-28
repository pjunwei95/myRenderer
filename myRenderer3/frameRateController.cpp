#include "frameRateController.h"
#include <Windows.h>
#include "engine.h"
#include <stdio.h>
#include "runMainLoop.h"


// Windows properties
LARGE_INTEGER nFrequency;

// get start
LARGE_INTEGER nStartTime;

// get elapsed time
// 1s = 1 000 000 micro s = 30 frames
LARGE_INTEGER  defaultFrameTime;

LARGE_INTEGER nStopTime;

//void StartTimer(TimerHandle*);
//void StopTimer(TimerHandle*);
//float GetTimerElapsedMs((TimerHandle*);
//float GetTimerElapsedSeconds((TimerHandle*);


void frameStart()
{
    QueryPerformanceFrequency(&nFrequency); //to be called only once. not per frame

    defaultFrameTime.QuadPart = 1000000 / FPS;

    QueryPerformanceCounter(&nStartTime);
}

void frameEnd()
{
    // get new elapsed time
    // if (new elapsed time - start
    QueryPerformanceCounter(&nStopTime);
}

bool isWithinFrameRate()
{
    nStopTime.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
    nStopTime.QuadPart /= nFrequency.QuadPart;
    if (nStopTime.QuadPart > defaultFrameTime.QuadPart) {
        printf("%.2f\n", (float)nStopTime.QuadPart / 1000);
        return true;
    }
    return false;
}


