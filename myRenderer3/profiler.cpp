#include "profiler.h"

bool isTrackProfile;
int count;


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