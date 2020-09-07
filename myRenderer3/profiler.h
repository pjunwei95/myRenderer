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
                                initialiseTimer();\
                                logmsg("Capturing profile for \"%s\":\n", #name);\
                                Timer pStartTime;\
                                updateTimeStamp(&pStartTime);\


#define PROFILE_END() \
                        Timer pStopTime;\
                        updateTimeStamp(&pStopTime);\
                        getTimerElapsedUs(&pStopTime, &pStartTime);\
                        logmsg("Time elapsed = %.2f ms\n", getTimerElapsedMs(&pStopTime));\


//#define PROFILE_FUNCTION()
#define PROFILE_INIT() setIsTrackProfile(false); setCount(50); \

#define TEST() setIsTrackProfile(true); setCount(0);\

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();
