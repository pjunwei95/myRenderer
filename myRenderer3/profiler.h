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
    profileStack.pop_back();\
}
//logmsg("Time elapsed for %s = %.2f ms\n", profile.profileName, getTimerElapsedMs(&profile.elapsed)); \


//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

#define PROFILE_INIT() \
initialiseTimer();\
setIsTrackProfile(false);\
setCount(50);

#define PROFILE_DUMP() \
for (int i = 0; i < profileStack.size(); i++)\
{\
    logmsg("Time elapsed for %s = %.2f ms\n", profileStack[i].profileName, getTimerElapsedMs(&profileStack[i].elapsed));\
}

// Header functions
void testProfiling();

void printProfile();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();

