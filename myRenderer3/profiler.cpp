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
    /*int arr[99][99];
    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            arr[i][j] = 1;
        }
    }
    int sum = 0;
    PROFILE_BEGIN(test1);
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        PROFILE_BEGIN(test2);
        for (int j = 0; j < sizeof(arr)/sizeof(arr[0]); j++)
        {
            sum += arr[i][j];
        }
        PROFILE_END(test2);
    }
    PROFILE_END(test1);*/
    //PROFILE_INIT();
    setProfile();
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

void setProfile()
{
    initialiseTimer(); 
    setCount(50);
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


std::deque<Profile> getProfileStack()
{
    return profileStack;
}

//void profileFrameTime()
//{
//    assert(!profileStack.empty());
//    for (int i = 0; i < profileStack.size; ++i)
//    {
//        Profile profile = profileStack[i];
//        updateTimeStamp(&profile.elapsed);
//        getTimerElapsedUs(&profile.elapsed, &profile.start);
//    }
//}






void setCount(int value)
{
    count = value;
}

int getCount()
{
    return count;
}

void addCount()
{
    ++count;
}