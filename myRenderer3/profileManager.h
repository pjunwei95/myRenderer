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
    ProfileManager(uint32_t frameNum, 
        const char* name,
        void(*cbBegin)(Profile*) = nullptr,
        void(*cbEnd)(Profile*) = nullptr
        )
    {
        frc.initialiseTimer();
    }

    ~ProfileManager() {}
    void beginProfile(Profile* profile) 
    {
        frc.updateTimeStamp(&profile->m_Start);
    }
    void endProfile() {}
    void onProfilerFlip() {}
    void(*cbBegin)(Profile*);
    void(*cbEnd)(Profile*);


private:
    FrameRateController frc;
};

void testProfiler(){}


