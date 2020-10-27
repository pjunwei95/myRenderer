#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"
#include "logger.h"
//#include "test.h"

#define MAX_CHAR 32

#define PROFILE_MACRO 0
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

    void Clear()
    {
        m_Children.clear();
    }

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

    void printStack()
    {
        uint32_t size = stack.size();
        for (uint32_t i = 0; i < size; ++i)
        {
            logmsg("stack[%d] = %s, %.2f ms, with %d child \n", i, stack[i]->m_Name, stack[i]->m_Duration, stack[i]->getChildrenSize());
        }
        logmsg("\n");
    }

    void UpdateProfileEntryParent()
    {
        if (stack.size() >= 2)
        {
            ProfileEntry& child = *stack.back();
            stack.popBack();
            ProfileEntry* parent = stack.back();
            parent->m_Children.pushBack(&child);
        }
    }

    void Clear()
    {
        stack.clear();
    }

    Array<ProfileEntry*>& GetStack()
    {
        return stack;
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
    e;

    //logmsg("===============================At EndProfile(%s)\n", e.m_Name);
    //gs_ProfileManager.printStack();

    gs_ProfileManager.UpdateProfileEntryParent();

}


void PrintProfile(ProfileEntry* e, uint32_t count)
{
#if 0
    //logmsg("=====================At PrintProfile(%s)\n", e->m_Name);
    //logmsg("name = %s, child = %d\n", e->m_Name, e->getChildrenSize());
    uint32_t tabNum = count++;
    while (tabNum-- > 0)
        logmsg("    ");
    logmsg("%s -> %.2f ms\n", e.m_Name, e.m_Duration);

    for (uint32_t i = 0; i < e.getChildrenSize(); ++i)
    {
        ProfileEntry& child = *e.m_Children[i];
        PrintProfile(child, count);
    }
#else
    //logmsg("=====================At PrintProfile(%s)\n", e->m_Name);
    //logmsg("name = %s, child = %d\n", e->m_Name, e->getChildrenSize());
    uint32_t tabNum = count++;
    while (tabNum-- > 0)
        logmsg("    ");
    logmsg("%s -> %.2f ms\n", e->m_Name, e->m_Duration);

    for (uint32_t i = 0; i < e->getChildrenSize(); ++i)
    {

        ProfileEntry* child = e->m_Children[i];
        PrintProfile(child, count);
    }
#endif
}