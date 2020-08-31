#pragma once
#include <Windows.h>

typedef LARGE_INTEGER * TimerHandle;
typedef LARGE_INTEGER Timer;


bool isWithinFrameRate(TimerHandle nStartTime, TimerHandle nStopTime, TimerHandle nFrequency, TimerHandle defaultFrameTime);

void StartTimer(TimerHandle nStartTime);

void StopTimer(TimerHandle nStopTime);

float GetTimerElapsedMs(TimerHandle nStopTime);

float GetTimerElapsedSeconds(TimerHandle nStopTime);
