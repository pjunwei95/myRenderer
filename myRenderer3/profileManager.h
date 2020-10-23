#pragma once
#include <assert.h>
#include <vector>
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"
#include "test.h"

#define MAX_CHAR 50

#define PROFILING 1
#if PROFILING
//#define PROFILE_BEGIN(name)
//#define PROFILE_END()
#define PROFILE_SCOPED(name) Stopwatch timer##name;
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION()
#endif

struct ProfileEntry
{
    ProfileEntry(const char* name)
        : m_Duration{ 0 }, m_Children{}, m_Name{}
    {
        strcpy_s(m_Name, MAX_CHAR, name);
    }

    uint32_t getChildrenSize() { return m_Children.size(); }

    Array<ProfileEntry*> m_Children;
    char m_Name[256];
    float m_Duration;
};

class ProfileManager
{
public:

    void RegisterProfileEntry(ProfileEntry& entry)
    {
        stack.pushBack(&entry);
    }

    void UpdateProfileEntryParent(ProfileEntry& entry)
    {
        stack.popBack();
        if (!stack.isEmpty())
        {
            ProfileEntry* parentProfileRef = stack.back();
            parentProfileRef->m_Children.pushBack(&entry);
        }
    }

    void PushToCircularBuffer()
    {

    }

private:
    Array<ProfileEntry*> stack;
};

static ProfileManager gs_ProfileManager;

void BeginProfile(ProfileEntry& e)
{
    gs_ProfileManager.RegisterProfileEntry(e);
}

void EndProfile(ProfileEntry& e)
{
    gs_ProfileManager.UpdateProfileEntryParent(e);
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

    //Separate timer functions
    Stopwatch timerTest;
    timerTest.start();
    Sleep(33);
    timerTest.stop();
    gs_DrawWindowProfileTag.m_Duration = timerTest.getDurationMs();

    EndProfile(gs_DrawWindowProfileTag);
    logmsg("End of scope, drawWindow took %.2f ms\n", gs_DrawWindowProfileTag.m_Duration);
}

void Outside()
{

    BeginProfile(gs_Foo);
    ///
    Stopwatch timerTest;
    timerTest.start();
    DrawWindow();
    DrawWindow();
    timerTest.stop();
    gs_Foo.m_Duration = timerTest.getDurationMs();
    ///
    EndProfile(gs_Foo);

    logmsg("Printing tags\n");
    logmsg("Foo -> %.2f ms\n", gs_Foo.m_Duration);

    for (uint32_t i = 0; i < gs_Foo.getChildrenSize(); ++i)
    {
        ProfileEntry* child = gs_Foo.m_Children[i];
        logmsg("    %s -> %.2f ms (children)\n", child->m_Name, child->m_Duration);
    }
}

void testSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
}

void testNestedProfile()
{
    LOG_UNIT_TEST();
    Outside();
}

void testProfileCircularBuffer()
{

}


void testProfile()
{
    LOG_TEST(Profiler);
    //for 1 frame
    testSimpleProfile();
    testNestedProfile();
    //for multiple frames
    testProfileCircularBuffer();
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
