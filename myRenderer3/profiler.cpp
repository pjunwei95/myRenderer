#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"

Array profileStack;

void initProfile()
{
    profileStack = createNewArray(sizeof(Profile));
}

void beginProfile(const char * string)
{
    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    updateTimeStamp(&profile.m_Start);
    pushBackArray(&profileStack, &profile); // stack push
}

void endProfile() 
{
    assert(!isArrayEmpty(&profileStack));
    //dereference from peek()
    Profile profile = *((Profile*)getArrayBack(&profileStack)); 
    updateTimeStamp(&profile.m_Elapsed);
    calcTimerElapsedUs(&profile.m_Elapsed, &profile.m_Start);
    logmsg("Time elapsed for |%s| profile = %.2f ms\n", profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
    popBackArray(&profileStack); //stack pop
}

void testProfiler()
{
    initialiseTimer();
    initProfile();
    beginProfile("test1");
        beginProfile("test2");
        Sleep(100);
        endProfile();
    Sleep(100);
    endProfile();
}
//
//void profileFrameTime(TimerHandle frameStart)
//{
//    Timer frameElapsedUs;
//    updateTimeStamp(&frameElapsedUs);
//    calcTimerElapsedUs(&frameElapsedUs, frameStart);
//    float frameElapsedMs = getTimerElapsedMs(&frameElapsedUs);
//    //logmsg("frametime #%d for %s = %.2f ms\n",)
//
//
//    for (int i = 0; i < profileStack.size(); ++i)
//    {
//        Profile profile = profileStack[i];
//        //logmsg("profileSize before pushing = %d bytes\n", sizeof profile);
//
//        if (profile.frameTimeDeque.size() > 50)
//        {
//            profile.frameTimeDeque.pop_front();
//        }
//        profile.frameTimeDeque.push_back(std::move(frameElapsedMs));
//        //logmsg("profileSize after pushing = %d bytes\n", sizeof profile);
//
//    }
//}
//
//void printProfile()
//{
//    if (!profileStack.empty())
//    {
//        for (int i = 0; i < profileStack.size(); ++i)
//        {
//            std::deque<float> frameQueue = profileStack[i].frameTimeDeque;
//            for (int j = 0; j < frameQueue.size(); ++j)
//            {
//                logmsg("frametime #%d for %s = %.2f ms\n", 
//                    frameQueue.size() - j,
//                    profileStack[i].profileName,
//                    frameQueue[j]);
//            }
//        }
//    }
//}

