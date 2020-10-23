#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"
#include "logger.h"
//#include "test.h"

#define MAX_CHAR 32

#define PROFILE_MACRO 1
#if PROFILE_MACRO
#define PROFILE_BEGIN(name) ProfileEntry entry_##name{ #name };\
                            BeginProfile(entry_##name);\
                            Stopwatch timer;\
                            timer.start()         

#define PROFILE_END(name)   timer.stop();\
                            entry_##name.m_Duration = timer.getDurationMs();\
                            EndProfile(entry_##name)

#define PROFILE_PRINT(name) PrintProfile(&entry_##name, 0);
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_BEGIN(name)
#define PROFILE_END(name)
#define PROFILE_PRINT(name)
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
    char m_Name[MAX_CHAR];
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

void PrintProfile(ProfileEntry* e, uint32_t count)
{
    uint32_t tabNum = count++;
    while (tabNum-- > 0)
        logmsg("    ");
    logmsg("%s -> %.2f ms\n", e->m_Name, e->m_Duration);
    
    for (uint32_t i = 0; i < e->getChildrenSize(); ++i)
    {
        ProfileEntry* child = e->m_Children[i];
        logmsg("    %s -> %.2f ms\n", child->m_Name, child->m_Duration);
    }
}
