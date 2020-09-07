#pragma once
#include "frameRateController.h"
#include "logger.h"

//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)
//
//
////each profiling blocks will store the CPU time in milli - seconds
////then you should have an option to dump out the profiling results to a text file
////for the past ~50 frames or so


#define PROFILE_BEGIN(name) \
                                Timer name##StartTime;\
                                updateTimeStamp(&name##StartTime);\


#define PROFILE_END(name) \
                        Timer name##StopTime;\
                        updateTimeStamp(&name##StopTime);\
                        getTimerElapsedUs(&name##StopTime, &name##StartTime);\
                        logmsg("Time elapsed for %s = %.2f ms\n", #name, getTimerElapsedMs(&name##StopTime));\


//#define PROFILE_FUNCTION()
#define PROFILE_INIT() initialiseTimer(); setIsTrackProfile(false); setCount(50); \

#define TEST() setIsTrackProfile(true); setCount(0);\

void testProfiling();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();
