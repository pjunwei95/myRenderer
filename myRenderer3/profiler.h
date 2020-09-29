#pragma once
#include "frameRateController.h"
#include "circularBuffer.h"
//#include <string.h>
//#include <cassert>

#define CHAR_MAX_LIMIT 256

struct Profile {
    Timer m_Start;
    Timer m_Elapsed;
    char m_ProfileName[CHAR_MAX_LIMIT];
};


//// Preprocessor functions
//#define PROFILE_BEGIN(name) \
//{\
//    Profile profile;\
//    strcpy_s(profile.profileName, sizeof profile.profileName, #name);\
//    updateTimeStamp(&profile.start);\
//    profile.isTrackProfile = true;\
//    std::deque<Profile> profileStack = getProfileStack();\
//    profileStack.push_back(profile);\
//}
//
//
//#define PROFILE_END() \
//{\
//    std::deque<Profile> profileStack = getProfileStack();\
//    if (!profileStack.empty()) \
//    {\
//        Profile profile = profileStack.back();\
//        updateTimeStamp(&profile.elapsed);\
//        calcTimerElapsedUs(&profile.elapsed, &profile.start);\
//        logmsg("Time elapsed for Profile %s = %.2f ms\n", \
//        profile.profileName, getTimerElapsedMs(&profile.elapsed));\
//        profileStack.pop_back();\
//    }\
//}


//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

void initProfile();

void printPastFrames();

// Header functions
void testProfiler();

void beginProfile(const char * string);

void endProfile();
