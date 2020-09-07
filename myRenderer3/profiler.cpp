#include "profiler.h"

bool isTrackProfile;
int count;

void testProfiling() 
{
    int arr[99][99];
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
    PROFILE_END(test1);
    //logmsg("sum = %d\n", sum);
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