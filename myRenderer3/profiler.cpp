#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"
#include "circularBuffer.h"
#include "stack.h"

//Array profileStack;

Stack* profileStack;
CircularBuffer frameCircBuf;

void initProfile(int frameNum)
{
    //profileStack = createNewArray(sizeof(Profile));
    profileStack = new Stack(sizeof(Profile));
    frameCircBuf = createNewCircBuf(frameNum, sizeof(Array));
}

Profile getProfile()
{
    Profile profile = *((Profile*)profileStack->Peek());
    assert(&profile);
    return profile;
}

void beginProfile(const char* string)
{
    assert(string);
    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    updateTimeStamp(&profile.m_Start);
    //pushBackArray(&profileStack, &profile); // stack push
    profileStack->Push(&profile);
}

void endProfile()
{
    //dereference from peek()
    Profile profile = getProfile();

    //update time elapsed
    updateTimeStamp(&profile.m_Elapsed);
    calcTimerElapsedUs(&profile.m_Elapsed, &profile.m_Start);

    /*logmsg("Time elapsed for |%s| profile = %.2f ms\n",
        profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));*/
    
    //popBackArray(&profileStack);
    profileStack->Pop();

}

void onProfilerFlip()
{
    //create array storing all the current profiles for that frame
    Array frameProfileList = createNewArray(sizeof(Profile));

    //iterate thru all profiles
    for (int i = 0; i < profileStack->Size(); ++i)
    {
        Profile* ptrToProfile = (Profile*) profileStack->At(i);
        // update time elapsed
        updateTimeStamp(&ptrToProfile->m_Elapsed);
        calcTimerElapsedUs(&ptrToProfile->m_Elapsed, &ptrToProfile->m_Start);
        pushBackArray(&frameProfileList, ptrToProfile);
    }

    //push array to circular buffer
    if (isFullCircBuf(&frameCircBuf))
    {
        popFrontCircBuf(&frameCircBuf);
    }
    pushBackCircBuf(&frameCircBuf, &frameProfileList);
    
}

void destroyProfile()
{
    //profile stack is destructed - ?

    //free each array in circular buffer
    for (int i = 0; i < getSizeCircBuf(&frameCircBuf); ++i)
    {
        //go through each frame in circular buffer
        Array frameProfileList = *((Array*)getCircBufAt(&frameCircBuf, i));
        freeArray(&frameProfileList);
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
            logmsg("Frame #%d, Time elapsed for |%s| profile = %.2f ms\n",
                i, profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
        }
    }
}

void testProfiler()
{
    for (int i = 0; i < 99; ++i)
    {
        beginProfile("test1");
        {
            beginProfile("nested");
            //simulate one frame = 33ms has passed
            Sleep(33);
            onProfilerFlip();
            endProfile();
        }
        endProfile();
    }
    //endProfile();
    //endProfile();
    printPastFrames();

    destroyProfile();
}

