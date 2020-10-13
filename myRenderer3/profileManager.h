#pragma once
#include "frameRateController.h"
#include <stdint.h>
#include "circularBuffer.h"
#include "array.h"

#define CHAR_MAX_LIMIT 256

struct Profile {
    Timer m_Start;
    Timer m_Elapsed;
    char m_ProfileName[CHAR_MAX_LIMIT];
};

class ProfileManager
{
public:
    ProfileManager();
    ~ProfileManager();
    void printPastFrames();
    void initProfile(uint32_t frameNum);
    void beginProfile(const char * string);
    void endProfile();
    void onProfilerFlip();
    void destroyProfile();
    void testProfiler();

    Profile* getProfile();

private:
    CircularBuffer<Array<Profile>>* frameCircBuf;
    FrameRateController frc;
    bool isProfileBegin; // This doesnt't work for nested profiling
};

void testProfiler();


