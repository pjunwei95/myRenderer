#pragma once
#include <Windows.h>

typedef LARGE_INTEGER TimerHandle;

//void frameStart();

//void frameStart(LARGE_INTEGER * nFrequency, LARGE_INTEGER * nStartTime, LARGE_INTEGER * defaultFrameTime);

//void frameStart(LARGE_INTEGER * nFrequency, LARGE_INTEGER * nStartTime);

//void frameEnd(LARGE_INTEGER * nStopTime);


//bool isWithinFrameRate(TimerHandle* nStartTime, TimerHandle* nStopTime, TimerHandle* nFrequency, TimerHandle* defaultFrameTime);

//bool isWithinFrameRate(TimerHandle* nStartTime, TimerHandle* nStopTime, LARGE_INTEGER* nFrequency, TimerHandle* defaultFrameTime);

bool isWithinFrameRate(TimerHandle* nStartTime, TimerHandle* nStopTime, TimerHandle* nFrequency, TimerHandle* defaultFrameTime);

void StartTimer(TimerHandle * nStartTime);

void StopTimer(TimerHandle * nStopTime);

float GetTimerElapsedMs(TimerHandle* nStopTime);

float GetTimerElapsedSeconds(TimerHandle* nStopTime);

//float GetTimerElapsedMs(LARGE_INTEGER* nStartTime, LARGE_INTEGER* nStopTime, LARGE_INTEGER* nFrequency);

//float GetTimerElapsedMs(LARGE_INTEGER * nStartTime, LARGE_INTEGER * nStopTime, LARGE_INTEGER * nFrequency);

//float GetTimerElapsedSeconds(LARGE_INTEGER * nStartTime, LARGE_INTEGER * nStopTime, LARGE_INTEGER * nFrequency);

//void frameEnd();

//bool isWithinFrameRate();
