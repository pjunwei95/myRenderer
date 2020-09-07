#pragma once
#include "frameRateController.h"
#include "logger.h"
#include "profiler.h"

//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)
//
//
////each profiling blocks will store the CPU time in milli - seconds
////then you should have an option to dump out the profiling results to a text file
////for the past ~50 frames or so
//
//#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
//PROFILE_CAPTURE(HeavyBlockOfCode);
//// Perform heavy CPU computation here
//PROFILE_END();

#define PROFILE_CAPTURE(name) \
                                logmsg("Capturing profile for \"%s\":\n", #name);\
                                Timer startTime;\
                                updateTimeStamp(&startTime);\


#define PROFILE_END() \
                        Timer stopTime;\
                        updateTimeStamp(&stopTime);\
                        getTimerElapsedUs(&stopTime, &startTime);\
                        logmsg("Time elapsed = %.2f ms\n", getTimerElapsedMs(&stopTime));\

