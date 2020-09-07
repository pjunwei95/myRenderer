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
                                Timer pStartTime;\
                                updateTimeStamp(&pStartTime);\


#define PROFILE_END(name) \
                        Timer pStopTime;\
                        updateTimeStamp(&pStopTime);\
                        getTimerElapsedUs(&pStopTime, &pStartTime);\
                        logmsg("Time elapsed for %s = %.2f ms\n", #name, getTimerElapsedMs(&pStopTime));\


//#define PROFILE_FUNCTION()
#define PROFILE_INIT() initialiseTimer(); setIsTrackProfile(false); setCount(50); \

#define TEST() setIsTrackProfile(true); setCount(0);\

void function();

void setIsTrackProfile(bool value);

bool getIsTrackProfile();

void setCount(int value);

int getCount();

void addCount();
