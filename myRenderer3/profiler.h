#pragma once
#include "frameRateController.h"
#include "logger.h"
#include <string.h>
#include <deque>
#include <cassert>

#define CHAR_MAX_LIMIT 256
#define STACK_MAX_LIMIT 50

struct Profile {
    Timer start;
    Timer elapsed;
    char profileName[CHAR_MAX_LIMIT];
};

// Preprocessor functions
#define PROFILE_BEGIN(name) \
if (profileStack.size() > STACK_MAX_LIMIT)\
{\
    profileStack.pop_front();\
}\
Profile name##profile;\
strcpy_s(name##profile.profileName, sizeof name##profile.profileName, #name);\
updateTimeStamp(&name##profile.start);\
profileStack.push_back(name##profile);

#define PROFILE_END() \
assert(!profileStack.empty());\
if (!profileStack.empty())\
{\
    Profile profile = profileStack.back();\
    updateTimeStamp(&profile.elapsed);\
    getTimerElapsedUs(&profile.elapsed, &profile.start);\
    logmsg("Time elapsed for %s = %.2f ms\n", profile.profileName, getTimerElapsedMs(&profile.elapsed));\
    profileStack.pop_back();\
}


//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

#define PROFILE_INIT() \
std::deque<Profile> profileStack;\
initialiseTimer();\
setIsTrackProfile(false);\
setCount(50);

// Header functions
void testProfiling();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();

