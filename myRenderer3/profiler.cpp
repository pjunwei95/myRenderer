#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"
#include "circularBuffer.h"
#include "stack.h"

Stack* profileStack;
CircularBuffer frameCircBuf;
FrameRateController frc;

void initProfile(int frameNum)
{
    frc.initialiseTimer();
    profileStack = new Stack(sizeof(Profile));
    frameCircBuf = createNewCircBuf(frameNum, sizeof(Array));
}

Profile getProfile()
{
    Profile profile = *((Profile*)profileStack->peek());
    assert(&profile);
    return profile;
}

void beginProfile(const char* string)
{
    assert(string);
    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    frc.updateTimeStamp(&profile.m_Start);
    profileStack->push(&profile);
}

void endProfile()
{
    //dereference from peek()
    Profile profile = getProfile();

    //update time elapsed
    frc.updateTimeStamp(&profile.m_Elapsed);
    frc.calcTimerElapsedUs(&profile.m_Elapsed, &profile.m_Start);

    profileStack->pop();
}

void onProfilerFlip()
{
    //create vector of profile for each frame
    //frame profile vector
    Array fpVec = createNewArray(sizeof(Profile));

    //iterate thru all profiles
    for (int i = 0; i < profileStack->size(); ++i)
    {
        Profile* ptrToProfile = (Profile*) profileStack->at(i);
        // update time elapsed
        frc.updateTimeStamp(&ptrToProfile->m_Elapsed);
        frc.calcTimerElapsedUs(&ptrToProfile->m_Elapsed, &ptrToProfile->m_Start);
        pushBackArray(&fpVec, ptrToProfile);
    }

    //push array to circular buffer
    if (isFullCircBuf(&frameCircBuf))
    {
        // when something is popped from circular buffer, it needs to be freed.
        Array* ptrFpVec = (Array*) popFrontCircBuf(&frameCircBuf);
        freeArray(ptrFpVec);
    }
    pushBackCircBuf(&frameCircBuf, &fpVec);
    
}

void destroyProfile()
{
    //profile stack is destructed
    profileStack->~Stack();

    //loop through circular buffer
    for (int i = 0; i < getSizeCircBuf(&frameCircBuf); ++i)
    {
        //get each vector of a frame
        Array fpVec = *((Array*)getCircBufAt(&frameCircBuf, i));
        freeArray(&fpVec);
    }

    //free circular buffer
    freeCircBuf(&frameCircBuf);
}

void printPastFrames()
{
    int tempFront = getFrontIdxCircBuf(&frameCircBuf);
    int size = getSizeCircBuf(&frameCircBuf);

    for (int i = 0; i < size; ++i)
    {
        //go through each frame in circular buffer
        int idx = (tempFront + i) % getCapacityCircBuff(&frameCircBuf);

        Array frameProfileList = *((Array*) getCircBufAt(&frameCircBuf, idx));
        for (int j = 0; j < getArraySize(&frameProfileList); ++j)
        {
            Profile* ptrToProfile = (Profile*)getArrayAt(&frameProfileList, j);
            Profile profile = *ptrToProfile;
            logmsg("Frame #%d, Time elapsed for |%s| profile = %.2f ms\n", i, profile.m_ProfileName, frc.getTimerElapsedMs(&profile.m_Elapsed));
            //formatting for profiler: frame#, profileName, startTime, endTime
            //logmsg("#%d, %s, %.2f\n", i, profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
        }
    }
}

void testProfiler()
{
    initProfile(50);
    for (int i = 0; i < 50; ++i)
    {
        beginProfile("test1");
        {
            //beginProfile("nested");
            //simulate one frame = 33ms has passed
            Sleep(33);
            onProfilerFlip();
            //endProfile();
        }
        endProfile();
    }
    printPastFrames();

    destroyProfile();
}

