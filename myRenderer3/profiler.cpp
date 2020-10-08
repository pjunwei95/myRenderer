#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"
#include "circularBuffer.h"
#include "stack.h"

Stack<Profile>* profileStack;
CircularBuffer<Array<Profile>>* frameCircBuf;
FrameRateController frc;
bool isProfileBegin; // This doesnt't work for nested profiling

void initProfile(uint32_t frameNum)
{
    frc.initialiseTimer();
    isProfileBegin = false;
    profileStack = new Stack<Profile>();
    frameCircBuf = new CircularBuffer<Array<Profile>>(frameNum);
}

Profile* getProfile()
{
    Profile* profile = (Profile*)profileStack->peek();
    assert(profile);
    return profile;
}

void beginProfile(const char* string)
{
    assert(string);
    assert(!isProfileBegin);
    isProfileBegin = true;

    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    frc.updateTimeStamp(&profile.m_Start);
    profileStack->push(&profile);
}

void endProfile()
{
    assert(isProfileBegin);
    isProfileBegin = false;

    //dereference from peek()
    Profile* profile = getProfile();

    //update time elapsed
    frc.updateTimeStamp(&profile->m_Elapsed);
    frc.calcTimerElapsedUs(&profile->m_Elapsed, &profile->m_Start);

    profileStack->pop();
}

void onProfilerFlip()
{
    //create vector of profile for each frame
    //frame profile vector
    //Array fpVec = createNewArray(sizeof(Profile));
    Array<Profile>* fpVec = new Array<Profile>();

    //iterate thru all profiles
    for (uint32_t i = 0; i < profileStack->size(); ++i)
    {
        Profile* ptrToProfile = (Profile*) profileStack->at(i);
         //update time elapsed
        frc.updateTimeStamp(&ptrToProfile->m_Elapsed);
        frc.calcTimerElapsedUs(&ptrToProfile->m_Elapsed, &ptrToProfile->m_Start);
        fpVec->pushBackArray(ptrToProfile);
    }

    //push array to circular buffer
    if (frameCircBuf->isFullCircBuf())
    {
         //when something is popped from circular buffer, it needs to be freed.
        Array<Profile>* ptrFpVec = (Array<Profile>*) frameCircBuf->popFrontCircBuf();
        ptrFpVec;
        //TODO handle memleak
        //freeArray(ptrFpVec);
        //delete ptrFpVec;
    }
    //pushBackCircBuf(&frameCircBuf, &fpVec);
    frameCircBuf->pushBackCircBuf(fpVec);
    
}

void destroyProfile()
{
    //profile stack is destructed
    delete profileStack;

    //TODO fix mem leak here for each array
    //Array<Profile>* foo = frameCircBuf->popFrontCircBuf();
    //delete foo;

    //free circular buffer
    delete frameCircBuf;
}

void printPastFrames()
{
    int tempFront = frameCircBuf->getFrontIdxCircBuf();
    int size = frameCircBuf->getSizeCircBuf();

    for (int i = 0; i < size; ++i)
    {
        //go through each frame in circular buffer
        int idx = (tempFront + i) % frameCircBuf->getCapacityCircBuff();

        //Array frameProfileList = *((Array*)frameCircBuf->getCircBufAt(&frameCircBuf, idx));
        Array<Profile>* frameProfileList = (Array<Profile>*)frameCircBuf->getCircBufAt(idx);
        for (uint32_t j = 0; j < frameProfileList->getArraySize(); ++j)
        {
            Profile* ptrToProfile = (Profile*)frameProfileList->getArrayAt(j);
            Profile profile = *ptrToProfile;
            logmsg("Frame #%d, Time elapsed for |%s| profile = %.2f ms\n", i, profile.m_ProfileName, frc.getTimerElapsedMs(&profile.m_Elapsed));
            //formatting for profiler: frame#, profileName, startTime, endTime
            //logmsg("#%d, %s, %.2f\n", i, profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
        }
    }
}

void testProfiler()
{
    uint32_t frameNum = 3;
    initProfile(frameNum);
    for (uint32_t i = 0; i < frameNum; ++i)
    {
        beginProfile(__FUNCDNAME__);
        {
            //beginProfile("nested");
            //simulate one frame = 33ms has passed
            Sleep(10);
            onProfilerFlip();
            //endProfile();
        }
        endProfile();
    }
    printPastFrames();

    destroyProfile();
}

