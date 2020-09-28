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

void beginProfile(const char* string, int stringSize)
{
    Profile profile;
    strcpy_s(profile.m_ProfileName, stringSize, string); //easy conversion to macros
    updateTimeStamp(&profile.m_Start);
    pushBackArray(&profileStack, &profile); // stack push
}

void endProfile()
{
    //dereference from peek()
    Profile profile = getProfile();
    updateTimeStamp(&profile.m_Elapsed);
    calcTimerElapsedUs(&profile.m_Elapsed, &profile.m_Start);

    Profile* ptrToProfile = &profile;
    pushBackCircBuf(&profileCircBuff, ptrToProfile);

    //logmsg("Time elapsed for |%s| profile = %.2f ms\n", 
        //profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
    popBackArray(&profileStack); //stack pop
}

void function()
{
    //int tempFront = cb->m_Front;

    int tempFront = getFrontIdxCircBuf(&profileCircBuff);

    //logmsg("=========\n");
    //for (int i = 0; i < getArrayCapacity(&cb->m_Array); ++i)
    int size = getSizeCircBuf(&profileCircBuff);
    for (int i = 0; i < size; ++i)
    {
        //int idx = (tempFront + i) % getArrayCapacity(&cb->m_Array);
        int idx = (tempFront + i) % getCapacityCircBuff(&profileCircBuff);
        //if (idx == cb->m_Back && !isFullCircBuf(cb))
            //break;
        //void* ptr = (uint8_t*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        //logmsg("%d ", *((int*)ptr));
    }
    //logmsg("\n==========\n");



    //logmsg("Time elapsed for |%s| profile = %.2f ms\n", 
        //profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
}

void testProfiler()
{
    initProfile();
    const char* firstTest = "test1";
    const char* secondTest = "test2";

    while (1) {
        if (isFullCircBuf(&profileCircBuff))
        {
            function();
        }


        beginProfile(firstTest, sizeof(firstTest));
            beginProfile(secondTest, sizeof(secondTest));
            Sleep(100);
            endProfile();
        Sleep(100);
        endProfile();
    }
}

void destroyProfiles();

