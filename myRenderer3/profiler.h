#pragma once
#include "frameRateController.h"
//#include <string.h>
//#include <cassert>

#define CHAR_MAX_LIMIT 256

struct Profile {
    Timer start;
    Timer elapsed;
    char profileName[CHAR_MAX_LIMIT];
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
//        getTimerElapsedUs(&profile.elapsed, &profile.start);\
//        logmsg("Time elapsed for Profile %s = %.2f ms\n", \
//        profile.profileName, getTimerElapsedMs(&profile.elapsed));\
//        profileStack.pop_back();\
//    }\
//}


//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

//#define PROFILE_INIT() \
//initialiseTimer();\
//setIsTrackProfile(false);\
//setCount(50);


void initProfile();

// Header functions
void testProfiling();

void beginProfile(const char * string);

void endProfile();

//void profileFrameTime(TimerHandle frameStart);
//
//void printProfile();

