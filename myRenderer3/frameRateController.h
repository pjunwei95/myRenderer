#pragma once
#include <Windows.h>

//void frameStart();

//void frameStart(LARGE_INTEGER * nFrequency, LARGE_INTEGER * nStartTime, LARGE_INTEGER * defaultFrameTime);

void frameStart(LARGE_INTEGER * nFrequency, LARGE_INTEGER * nStartTime);

void frameEnd(LARGE_INTEGER * nStopTime);

bool isWithinFrameRate(LARGE_INTEGER * nStopTime, LARGE_INTEGER * nStartTime, LARGE_INTEGER * nFrequency, LARGE_INTEGER * defaultFrameTime);

void StartTimer(LARGE_INTEGER * nStartTime);

void StopTimer(LARGE_INTEGER * nStopTime);

//float GetTimerElapsedMs(LARGE_INTEGER * nStartTime, LARGE_INTEGER * nStopTime, LARGE_INTEGER * nFrequency);

//float GetTimerElapsedSeconds(LARGE_INTEGER * nStartTime, LARGE_INTEGER * nStopTime, LARGE_INTEGER * nFrequency);

//void frameEnd();

//bool isWithinFrameRate();
