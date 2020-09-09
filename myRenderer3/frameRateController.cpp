#include "frameRateController.h"
#include "engine.h"
#include <stdio.h>

Timer nFrequency;
Timer defaultFrameTime;

void initialiseTimer()
{
    // 1s = 1 000 000 micro s = 30 frames
    defaultFrameTime.QuadPart = 1000000 / FPS; // unit is in seconds, NOT microseconds

    QueryPerformanceFrequency(&nFrequency); //to be called only once. not per frame
}

void idleUntilFPSLimit(TimerHandle timer)
{
    while (1) // frame drawing and blocking, or at gameStateCurr == next
    {
        if (isWithinFrameRate(timer))
        {
            break;
        }
    }
}


bool isWithinFrameRate(TimerHandle nStartTime)
{
    Timer nStopTime;
    updateTimeStamp(&nStopTime);

    getTimerElapsedUs(&nStopTime, nStartTime);
    if (nStopTime.QuadPart > defaultFrameTime.QuadPart) {
        //printf("frametime = %.2f ms\n", getTimerElapsedMs(&nStopTime));
        //printf("frametime = %f s\n", GetTimerElapsedSeconds(nStopTime));
        //logmsg("FPS = %f \n", 1.0 / getTimerElapsedSeconds(&nStopTime));
        return true;
    }
    return false;
}

void getTimerElapsedUs(TimerHandle nStopTime, const TimerHandle nStartTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart); //the units here are in seconds
    nStopTime->QuadPart *= 1000000; //convert seconds to microseconds
    nStopTime->QuadPart /= nFrequency.QuadPart;
}

void updateTimeStamp(TimerHandle timer)
{
    QueryPerformanceCounter(timer);
}

float getTimerElapsedMs(const TimerHandle timeElapsed)
{
    return (float) timeElapsed->QuadPart / 1000;
}

float getTimerElapsedSeconds(const TimerHandle timeElapsed)
{
    return (float)timeElapsed->QuadPart / 1000000;
}