#pragma once
#include <assert.h>
#include <vector>
#include "timer.h"
#include "array.h"
#include "circularBuffer.h"

//#define PROFILE_BEGIN(name)
//#define PROFILE_END()
//#define PROFILE_FUNCTION()
//#define PROFILE_SCOPED(name)
#define MAX_CHAR 256




struct ProfileEntry
{
    ProfileEntry()
        : m_Duration{ 0 }, m_Children{}, m_Name{}
    {
    }

    ProfileEntry(const char* name)
        : m_Duration{ 0 }, m_Children{}, m_Name{}
    {
        strcpy_s(m_Name, MAX_CHAR, name);
    }

    Array<ProfileEntry*> m_Children;
    char m_Name[256];
    float m_Duration;
};

class ProfileManager
{
public:
    ProfileManager()
        : cb{50}
    {
    }

    void RegisterProfileEntry(ProfileEntry& entry)
    {
        //if stack is not empty, register it as children?
        if (!stack.isEmpty()) //profile is a child
        {
            ProfileEntry parent = stack.back();
            parent.m_Children.pushBack(&entry);
        }
        //push to stack
        stack.pushBack(entry);
    }

    void UpdateProfileEntryTime(ProfileEntry& entry, float timeElapsed)
    {
        entry.m_Duration = timeElapsed;
    }

    bool IsAncestor()
    {
        if (!stack.isEmpty() && stack.size() == 1)
            return true;
        return false;
    }

    void UpdateProfileEntryHeirarchy(ProfileEntry& entry)
    {
        //if is an ancestor, push to listOfAncestor
        if (IsAncestor())
            listOfAncestor.pushBack(&entry);
        //pop ancestor/child
        stack.popBack();
    }

    void PushToCircularBuffer() 
    {
        cb.pushBack(listOfAncestor);
    }

private:
    CircularBuffer<Array<ProfileEntry*>> cb;
    Array<ProfileEntry> stack;
    Array<ProfileEntry*> listOfAncestor;
};


static ProfileManager gs_ProfileManager;

static Timer timer;

void BeginProfile(ProfileEntry& e)
{
    Timer::Clock m_StartTime;
    timer.updateTimeStamp(m_StartTime);
    gs_ProfileManager.RegisterProfileEntry(e);
}

void EndProfile(ProfileEntry& e)
{
    timer.stop();
    float timeElapsed = timer.getDurationMs();
    gs_ProfileManager.UpdateProfileEntryTime(e, timeElapsed);
    gs_ProfileManager.UpdateProfileEntryHeirarchy(e);
}

void OnProfileFlip()
{
    gs_ProfileManager.PushToCircularBuffer();
}

///////////////////////////////////////////////

ProfileEntry gs_DrawWindowProfileTag{ "DrawWindowProfileTag" };
ProfileEntry gs_Foo{ "Foo" };
void DrawWindow()
{
    BeginProfile(gs_DrawWindowProfileTag);

    ///
    Sleep(33);

    EndProfile(gs_DrawWindowProfileTag);
}

void Outside()
{

    BeginProfile(gs_Foo);
    ///

    DrawWindow();
    DrawWindow();

    ///
    EndProfile(gs_Foo);
}

void testProfile()
{
    for (int i = 0; i < 30; ++i)
    {
        Outside();
        OnProfileFlip();
    }
}

































//#include "frameRateController.h"
//#include <stdint.h>
//#include "circularBuffer.h"
//#include "array.h"
//#include "logger.h"
//
//#define CHAR_MAX_LIMIT 256
//
//struct Profile {
//    const char* getString() { return m_Name; }
//    Timer m_Start;
//    Timer m_Elapsed;
//    char m_Name[CHAR_MAX_LIMIT];
//    Profile() {}
//    ~Profile() {}
//};
//
//class ProfileManager
//{
//public:
//    ProfileManager(uint32_t frameNum)
//        : cb{ frameNum }
//    {
//        frc.initialiseTimer();
//    }
//
//    void profileBegin(const char* name)
//    {
//        Profile* ptrProfile = findProfile(name);
//        if (ptrProfile)
//        {
//            frc.updateTimeStamp(ptrProfile->m_Start);
//        }
//        else
//        {
//            Profile newProfile;
//            strcpy_s(newProfile.m_Name, CHAR_MAX_LIMIT, name);
//            frc.updateTimeStamp(newProfile.m_Start);
//            profileArr.pushBack(newProfile);
//        }
//    }
//
//    void profileEnd(const char* name)
//    {
//        Profile* ptrProfile = findProfile(name);
//        assert(ptrProfile);
//        frc.updateTimeStamp(ptrProfile->m_Elapsed);
//        frc.calcTimerElapsedUs(ptrProfile->m_Elapsed, ptrProfile->m_Start);
//    }
//
//    void onProfilerFlip()
//    {
//        if (cb.isFull())
//            Array<Profile> oldestFrame = cb.popFront();
//        cb.pushBack(profileArr);
//    }
//
//    Profile* findProfile(const char* name)
//    {
//        uint32_t listSize = profileArr.size();
//        for (uint32_t i = 0; i < listSize; ++i)
//        {
//            if (0 == strcmp(profileArr[i].getString(), name))
//                return &profileArr[i];
//        }
//        return nullptr;
//    }
//
//    void printPastFrames()
//    {
//        uint32_t cbSize = cb.size();
//        for (uint32_t i = 0; i < cbSize; ++i)
//        {
//            Array<Profile> foo = cb.at(i);
//            uint32_t arrSize = foo.size();
//            logmsg("cbSize = %d, each frame has %d profiles\n", cbSize, arrSize);
//            for (uint32_t j = 0; j < arrSize; ++j)
//            {
//                Profile p = foo[j];
//                logmsg("Frame #%d, Time elapsed for |%s| profile = %.2f ms\n", i, p.getString(), frc.getTimerElapsedMs(p.m_Elapsed));
//            }
//        }
//    }
//
//private:
//    FrameRateController frc;
//    Array<Profile> profileArr;
//    CircularBuffer<Array<Profile>> cb;
//};
//
//
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
