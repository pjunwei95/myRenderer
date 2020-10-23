#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"
//#include "logger.h"
//#include "test.h"

#define MAX_CHAR 50

//#define PROFILING
#if PROFILING
#define PROFILE_BEGIN(name) ProfileEntry entry_##name{ #name };\
                            BeginProfile(entry_##name);\
                            Stopwatch timer;\
                            timer.start()         

#define PROFILE_END(name)   timer.stop();\
                            entry_##name.m_Duration = timer.getDurationMs();\
                            EndProfile(entry_##name)

#define PROFILE_PRINT(name) PrintProfile(entry_##name, 0);
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_BEGIN(name)
#define PROFILE_END(name)
#define PROFILE_PRINT(name) logmsg(#name" took %.2f ms\n", entry_##name.m_Duration)
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

void PrintProfile(ProfileEntry& e, uint32_t count)
{
    uint32_t tabNum = count;
    while (tabNum-- > 0)
        logmsg("    ");
    logmsg("%s -> %.2f ms\n", e.m_Name, e.m_Duration);
    uint32_t numOfChildren = e.getChildrenSize();

    if (numOfChildren != 0)
        for (uint32_t i = 0; i < numOfChildren; ++i)
        {
            ProfileEntry& child = *e.m_Children[i];
            PrintProfile(child, ++count);
        }
}

//////////////////////////////////////////////////////////////
//Simulated main functions

ProfileEntry gs_DrawWindowProfileTag{ "DrawWindowProfileTag" };
ProfileEntry gs_Foo{ "Foo" };
void DrawWindow()
{
    BeginProfile(gs_DrawWindowProfileTag);
    //Separate timer functions
    Stopwatch timer;
    timer.start();

    Sleep(33);
    timer.stop();
    gs_DrawWindowProfileTag.m_Duration = timer.getDurationMs();

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
    PrintProfile(gs_Foo, 0);
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
#if PROFILING
void DrawWindowWithMacro()
{
    PROFILE_BEGIN(DrawWindowProfile);
    ///
    Sleep(33);
    ///
    PROFILE_END(DrawWindowProfile);
    PROFILE_PRINT(DrawWindowProfile);
}


void OutsideWithMacro()
{
    PROFILE_BEGIN(Foo);
    ///
    DrawWindowWithMacro();
    DrawWindowWithMacro();
    ///
    PROFILE_END(Foo);
    PROFILE_PRINT(Foo);
}


void testSimpleProfileWithMacro()
{
    LOG_UNIT_TEST();
    DrawWindowWithMacro();
}

void testNestedProfileWithMacro()
{
    LOG_UNIT_TEST();
    OutsideWithMacro();
}
#endif

void testProfileCircularBuffer()
{

}

void testProfileManager()
{
    LOG_TEST(Profiler);
    //Without Macros
    testSimpleProfile();
    testNestedProfile();
    //With Macros
#if PROFILING
    testSimpleProfileWithMacro();
    testNestedProfileWithMacro();
#endif
    //for multiple frames
    testProfileCircularBuffer();
}
