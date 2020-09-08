#pragma once
#include "frameRateController.h"
#include "logger.h"

//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)

#define PROFILE_BEGIN(name) \
Timer name##StartTime;\
updateTimeStamp(&name##StartTime);
//struc Profile{
//char profName[];
//Timer start;
//Timer elapsedTime;
//}
//Profile &name##profile;
//profile.name = #name
//updateTimeStamp(&profile.start); 
//

#define PROFILE_END(name) \
Timer name##StopTime;\
updateTimeStamp(&name##StopTime);\
getTimerElapsedUs(&name##StopTime, &name##StartTime);\
logmsg("Time elapsed for %s = %.2f us\n", #name, &name##StopTime.QuadPart);
//logmsg("Time elapsed for %s = %.2f ms\n", #name, getTimerElapsedMs(&name##StopTime));\
//Timer name##StopTime;\
//updateTimeStamp(&name##StopTime);\
//getTimerElapsedUs(&name##StopTime, &profile.StartTime);\
//profile.elapsedTime.quadpart = profile.stopTime.quadpart;

//#define PROFILE_FUNCTION()


#define PROFILE_INIT() initialiseTimer(); setIsTrackProfile(false); setCount(50); \

#define PROFILE_TRACK() setIsTrackProfile(true); setCount(0);\

void testProfiling();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();
