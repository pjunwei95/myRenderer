#pragma once
#include "frameRateController.h"
#include "logger.h"

//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

#define PROFILE_BEGIN(name) \
Timer name##StartTime;\
updateTimeStamp(&name##StartTime);

#define PROFILE_END(name) \
Timer name##StopTime;\
updateTimeStamp(&name##StopTime);\
getTimerElapsedUs(&name##StopTime, &name##StartTime);\
logmsg("Time elapsed for %s = %.2f ms\n", #name, getTimerElapsedMs(&name##StopTime));

void profileInit();

#define PROFILE_TRACK() setIsTrackProfile(true); setCount(0);\

void testProfiling();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();
