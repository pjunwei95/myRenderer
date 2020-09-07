#pragma once
#include <Windows.h>

typedef LARGE_INTEGER Timer;

typedef LARGE_INTEGER * TimerHandle;

void initialiseTimer();

void idleUntilFPSLimit(TimerHandle timer);

bool isWithinFrameRate(TimerHandle nStartTime);

void getTimerElapsedUs(TimerHandle nStopTime, const TimerHandle nStartTime);

void updateTimeStamp(TimerHandle nStartTime);

float getTimerElapsedMs(TimerHandle nStopTime);

float getTimerElapsedSeconds(TimerHandle nStopTime);
