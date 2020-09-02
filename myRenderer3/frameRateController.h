#pragma once
#include <Windows.h>

typedef LARGE_INTEGER Timer;

typedef LARGE_INTEGER * TimerHandle;

void initialiseTimer();

bool isWithinFrameRate(TimerHandle nStartTime, TimerHandle nStopTime);

void startTimer(TimerHandle nStartTime);

void stopTimer(TimerHandle nStopTime);

float getTimerElapsedMs(TimerHandle nStopTime);

float getTimerElapsedSeconds(TimerHandle nStopTime);
