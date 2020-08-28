#include "frameRateController.h"
#include <Windows.h>
#include "engine.h"
#include <stdio.h>

// Windows properties
LARGE_INTEGER nFrequency;

// get start
LARGE_INTEGER nStartTime;

// get elapsed time
// 1s = 1 000 000 micro s = 30 frames
LARGE_INTEGER  defaultFrameTime;

LARGE_INTEGER nStopTime;

void frameStart()
{
    QueryPerformanceFrequency(&nFrequency);

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
