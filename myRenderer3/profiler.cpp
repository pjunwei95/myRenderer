#include "profiler.h"
#include <string>

bool isTrackProfile;
int count;

class Profile {
public:
    std::string profName;
    Timer startTime;
};

void function() 
{
    /*PROFILE_BEGIN(first loop);
    for (int i = 0; i < 50; i++)
    {
        PROFILE_BEGIN(second loop);
        for (int j = 0; j < 50; j++)
        {
            PROFILE_END(second loop);
        }
        PROFILE_END(first loop);
    }*/

    //struc/class containing
    //name
    //timeElapsed


//#define PROFILE_BEGIN(name) \

    //Profile profile;
    //profile.profname = #name;
    //updateTimeStamp(&profile.startTime);\
//
//
//#define PROFILE_END(name) \
    // 


//                        Timer pStopTime;\
//                        updateTimeStamp(&pStopTime);\
//                        getTimerElapsedUs(&pStopTime, &pStartTime);\
//                        logmsg("Time elapsed for %s = %.2f ms\n", #name, getTimerElapsedMs(&pStopTime));\

}

void setIsTrackProfile(bool value)
{
    isTrackProfile = value;
}

bool getIsTrackProfile()
{
    return isTrackProfile;
}

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