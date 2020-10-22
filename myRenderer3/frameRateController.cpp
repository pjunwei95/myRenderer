#include "frameRateController.h"
#include "engine.h"
#include <stdio.h>
//#include "profiler.h"

FrameRateController::FrameRateController()
{
    // 1s = 1 000 000 micro s = 30 frames
    m_DefaultFrameTime.QuadPart = 1000000 / FPS; // unit is in seconds, NOT microseconds
}


void FrameRateController::idleUntilFPSLimit(Stopwatch timer)
{
    while (1) // frame drawing and blocking, or at gameStateCurr == next
    {
        if (isWithinFrameRate(timer))
        {
            break;
        }
    }
}

bool FrameRateController::isWithinFrameRate(Stopwatch timer)
{
    timer.stop();
    Stopwatch::Timer duration = timer.getDurationUs();
    if (duration.QuadPart > m_DefaultFrameTime.QuadPart) {
        //printf("frametime = %.2f ms\n", getTimerElapsedMs(&nStopTime));
        //printf("frametime = %f s\n", GetTimerElapsedSeconds(nStopTime));
        //logmsg("FPS = %f \n", 1.0 / getTimerElapsedSeconds(&nStopTime));
        logmsg("FPS = %f \n", 1.0 / timer.getDurationSeconds());
        return true;
    }
    return false;
}