#include "profiler.h"
#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"

struct Stack* profileStack;


void testStack()
{
    
}

void initProfile()
{
    profileStack = createStack(100);
}

void testProfiling() 
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




void beginProfile(const char * string)
{
    Profile profile;
    strcpy_s(profile.profileName, sizeof(profile.profileName), string); //easy conversion to macros
    updateTimeStamp(&profile.start);
    push(profileStack, profile);
}

void endProfile() 
{
    assert(!isEmpty(profileStack));
    Profile profile = peek(profileStack);
    updateTimeStamp(&profile.elapsed);
    getTimerElapsedUs(&profile.elapsed, &profile.start);
    logmsg("Time elapsed for |%s| profile = %.2f ms\n", profile.profileName, getTimerElapsedMs(&profile.elapsed));
    pop(profileStack);
}
//
//void profileFrameTime(TimerHandle frameStart)
//{
//    Timer frameElapsedUs;
//    updateTimeStamp(&frameElapsedUs);
//    getTimerElapsedUs(&frameElapsedUs, frameStart);
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

