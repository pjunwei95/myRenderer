#pragma once
#include "frameRateController.h"

#define CHAR_MAX_LIMIT 256

struct Profile {
    Timer m_Start;
    Timer m_Elapsed;
    char m_ProfileName[CHAR_MAX_LIMIT];
};

void printPastFrames();

// Header functions
void testProfiler();

void initProfile(int frameNum);

void beginProfile(const char * string);

void endProfile();

void onProfilerFlip();

void destroyProfile();
