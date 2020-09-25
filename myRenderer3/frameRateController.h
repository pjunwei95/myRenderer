#pragma once
#include <Windows.h>

typedef LARGE_INTEGER Timer;

typedef LARGE_INTEGER * TimerHandle;

void initialiseTimer();

void idleUntilFPSLimit(TimerHandle timer);

bool isWithinFrameRate(TimerHandle nStartTime);

void calcTimerElapsedUs(TimerHandle nStopTime, const TimerHandle nStartTime);

void updateTimeStamp(TimerHandle timer);

float getTimerElapsedMs(const TimerHandle timeElapsed);

float getTimerElapsedSeconds(const TimerHandle timeElapsed);

