#pragma once
#include "frameRateController.h"
#include "logger.h"
#include <string.h>
#include <deque>
#include <cassert>

#define CHAR_MAX_LIMIT 256


// Preprocessor functions
#define PROFILE_BEGIN(name) beginProfile(#name);
//Profile name##profile;\
//strcpy_s(name##profile.profileName, sizeof name##profile.profileName, #name);\
//updateTimeStamp(&name##profile.start);\
//profileStack.push_back(name##profile);

#define PROFILE_END() endProfile();
//assert(!profileStack.empty());\
//if (!profileStack.empty())\
//{\
//Profile profile = profileStack.back();\
//updateTimeStamp(&profile.elapsed);\
//getTimerElapsedUs(&profile.elapsed, &profile.start);\
//logmsg("Time elapsed for %s = %.2f ms\n", profile.profileName, getTimerElapsedMs(&profile.elapsed)); \
//profileStack.pop_back();\
//}


//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

//#define PROFILE_INIT() \
//initialiseTimer();\
//setIsTrackProfile(false);\
//setCount(50);


// Header functions
void testProfiling();

void setProfile();

void beginProfile(const char * string);

void endProfile();

void setCount(int value);

int getCount();

void addCount();

