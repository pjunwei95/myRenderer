#include "frameRateController.h"
#include "engine.h"
#include <stdio.h>
#include "circularBuffer.h"
#include "profiler.h"

void FrameRateController::initialiseTimer()
{
    // 1s = 1 000 000 micro s = 30 frames
    m_DefaultFrameTime.QuadPart = 1000000 / FPS; // unit is in seconds, NOT microseconds

    QueryPerformanceFrequency(&m_Frequency); //to be called only once. not per frame
}

void FrameRateController::idleUntilFPSLimit(TimerHandle timer)
{
    while (1) // frame drawing and blocking, or at gameStateCurr == next
    {
        if (isWithinFrameRate(timer))
        {
            break;
        }
    }
}


bool FrameRateController::isWithinFrameRate(TimerHandle nStartTime)
{
    Timer nStopTime;
    updateTimeStamp(&nStopTime);

    calcTimerElapsedUs(&nStopTime, nStartTime);
    if (nStopTime.QuadPart > m_DefaultFrameTime.QuadPart) {
        //printf("frametime = %.2f ms\n", getTimerElapsedMs(&nStopTime));
        //printf("frametime = %f s\n", GetTimerElapsedSeconds(nStopTime));
        //logmsg("FPS = %f \n", 1.0 / getTimerElapsedSeconds(&nStopTime));
        return true;
    }
    return false;
}

void FrameRateController::calcTimerElapsedUs(TimerHandle nStopTime, const TimerHandle nStartTime)
{
    nStopTime->QuadPart = (nStopTime->QuadPart - nStartTime->QuadPart); //the units here are in seconds
    nStopTime->QuadPart *= 1000000; //convert seconds to microseconds
    nStopTime->QuadPart /= m_Frequency.QuadPart;
}

void FrameRateController::updateTimeStamp(TimerHandle timer)
{
    QueryPerformanceCounter(timer);
}

float FrameRateController::getTimerElapsedMs(const TimerHandle timeElapsed)
{
    return (float) timeElapsed->QuadPart / 1000;
}

float FrameRateController::getTimerElapsedSeconds(const TimerHandle timeElapsed)
{
    return (float)timeElapsed->QuadPart / 1000000;
}