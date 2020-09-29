#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"
#include "circularBuffer.h"

Array profileStack;
CircularBuffer profileCircBuff;

void initProfile()
{
    profileStack = createNewArray(sizeof(Profile));
    profileCircBuff = createNewCircBuf(50, sizeof(Profile));
}

Profile getProfile()
{
    assert(!isArrayEmpty(&profileStack));
    Profile profile = *((Profile*)getArrayBack(&profileStack));
    return profile;
}

void beginProfile(const char* string)
{
    assert(string);
    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    updateTimeStamp(&profile.m_Start);
    pushBackArray(&profileStack, &profile); // stack push
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

    //circular Buffer operations
    Profile* ptrToProfile = &profile;
    
    if (isFullCircBuf(&profileCircBuff))
    {
        popFrontCircBuf(&profileCircBuff);
    }
    pushBackCircBuf(&profileCircBuff, ptrToProfile);

    //pop stack
    popBackArray(&profileStack); //stack pop
}

void destroyProfile()
{
    freeArray(&profileStack);
    freeCircBuf(&profileCircBuff);
}

void printPastFrames()
{
    int tempFront = getFrontIdxCircBuf(&profileCircBuff);
    int size = getSizeCircBuf(&profileCircBuff);

    for (int i = 0; i < size; ++i)
    {
        int idx = (tempFront + i) % getCapacityCircBuff(&profileCircBuff);
        Profile* ptrToProfile = (Profile*) getCircBufAt(&profileCircBuff, idx);
        Profile profile = *ptrToProfile;
        logmsg("Time elapsed for |%s| profile = %.2f ms\n", 
            profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed)); 
    }
}

void testProfiler()
{
    initProfile();
    //const char* firstTest = "test1";
    //const char* secondTest = "test2";
    
    while (1) {
        if (isFullCircBuf(&profileCircBuff))
        {
            printPastFrames();
            break;
        }


        beginProfile("test1");
            beginProfile("test2");
            Sleep(10);
            endProfile();
        Sleep(10);
        endProfile();
    }
    destroyProfile();
}

