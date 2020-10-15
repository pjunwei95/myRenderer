#pragma once
#include "frameRateController.h"
#include <stdint.h>
#include "circularBuffer.h"
#include "array.h"
#include "logger.h"

#define CHAR_MAX_LIMIT 256

struct Profile {
    const char* getString() { return m_Name; }
    Timer m_Start;
    Timer m_Elapsed;
    char m_Name[CHAR_MAX_LIMIT];
};

class ProfileManager
{
public:
    ProfileManager(uint32_t frameNum)
        : cb{ frameNum }
    {
        frc.initialiseTimer();
    }

    void profileBegin(const char* name, uint32_t size)
    {
        Profile* ptrProfile = findProfile(name);
        if (ptrProfile)
        {
            frc.updateTimeStamp(ptrProfile->m_Start);
        }
        else
        {
            Profile newProfile;
            strcpy_s(newProfile.m_Name, size, name);
            frc.updateTimeStamp(newProfile.m_Start);
            profileArr.pushBack(newProfile);
        }
    }

    void profileEnd(const char* name)
    {
        Profile* ptrProfile = findProfile(name);
        assert(ptrProfile);
        frc.updateTimeStamp(ptrProfile->m_Elapsed);
        frc.calcTimerElapsedUs(ptrProfile->m_Elapsed, ptrProfile->m_Start);
    }

    void onProfilerFlip()
    {
        if (cb.isFull())
            Array<Profile> oldestFrame = cb.popFront();
        cb.pushBack(profileArr);
    }

    Profile* findProfile(const char* name)
    {
        uint32_t listSize = profileArr.size();
        for (uint32_t i = 0; i < listSize; ++i)
        {
            if (0 == strcmp(profileArr[i].getString(), name))
                return &profileArr[i];
        }
        return nullptr;
    }
private:
    FrameRateController frc;
    Array<Profile> profileArr;
    CircularBuffer<Array<Profile>> cb;
};


//void ProfileManager::onProfilerFlip()
//{
//    //create vector of profile for each frame
//    //frame profile vector
//    //Array fpVec = createNewArray(sizeof(Profile));
//    Array<Profile>* fpVec = new Array<Profile>();
//
//    //iterate thru all profiles
//    for (uint32_t i = 0; i < profileStack->size(); ++i)
//    {
//        Profile* ptrToProfile = (Profile*) profileStack->at(i);
//         //update time elapsed
//        frc.updateTimeStamp(&ptrToProfile->m_Elapsed);
//        frc.calcTimerElapsedUs(&ptrToProfile->m_Elapsed, &ptrToProfile->m_Start);
//        fpVec->pushBack(ptrToProfile);
//    }
//
//    //push array to circular buffer
//    if (frameCircBuf->isFull())
//    {
//         //when something is popped from circular buffer, it needs to be freed.
//        Array<Profile>* ptrFpVec = (Array<Profile>*) frameCircBuf->popFront();
//        ptrFpVec;
//        //TODO handle memleak
//        //freeArray(ptrFpVec);
//        //delete ptrFpVec;
//    }
//    //pushBackCircBuf(&frameCircBuf, &fpVec);
//    frameCircBuf->pushBack(fpVec);
//    
//}
//