#include "profiler.h"


struct Profile {
    Timer start;
    Timer elapsed;
    char profileName[CHAR_MAX_LIMIT];
    std::deque<float> frameTimeDeque;
    bool isTrackProfile = false;
};
int count;
std::deque<Profile> profileStack;


void testProfiling() 
{
    initialiseTimer();
    PROFILE_BEGIN(test1);
    Sleep(100);
    {
        PROFILE_BEGIN(test2);
        Sleep(100);
        PROFILE_END();
        //endProfile();
    }
    //endProfile();
    PROFILE_END();
}


void beginProfile(const char * string)
{
    Profile profile;
    strcpy_s(profile.profileName, sizeof profile.profileName, string);
    updateTimeStamp(&profile.start);
    profile.isTrackProfile = true;
    profileStack.push_back(profile);
}

void endProfile() 
{
    assert(!profileStack.empty());
    if (!profileStack.empty()) //TODO to remove if statement
    {
        Profile profile = profileStack.back();
        updateTimeStamp(&profile.elapsed);
        getTimerElapsedUs(&profile.elapsed, &profile.start);
        logmsg("Time elapsed for Profile %s = %.2f ms\n", profile.profileName, getTimerElapsedMs(&profile.elapsed));
        profileStack.pop_back();
    }
}

void profileFrameTime(TimerHandle frameStart)
{
    if (!profileStack.empty()) {
        Timer frameElapsedUs;
        updateTimeStamp(&frameElapsedUs);
        getTimerElapsedUs(&frameElapsedUs, frameStart);
        float frameElapsedMs = getTimerElapsedMs(&frameElapsedUs);

        for (int i = 0; i < profileStack.size(); ++i)
        {
            std::deque<float> frameQueue = profileStack[i].frameTimeDeque;
            if (frameQueue.size() > 50)
            {
                frameQueue.pop_front();
            }
            frameQueue.push_back(frameElapsedMs);
        }
    }
}

void printProfile()
{
    if (!profileStack.empty())
    {
        for (int i = 0; i < profileStack.size(); ++i)
        {
            std::deque<float> frameQueue = profileStack[i].frameTimeDeque;
            for (int j = 0; j < frameQueue.size(); ++j)
            {
                logmsg("frametime #%d for %s = %.2f ms\n", 
                    frameQueue.size() - j,
                    profileStack[i].profileName,
                    frameQueue[j]);
            }
        }
    }
}
