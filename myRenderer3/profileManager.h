#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "logger.h"

#define MAX_CHAR 320

struct ProfileEntry
{
   /* Array<ProfileEntry*> m_Children;*/
    const char* m_Name;
    float m_Duration;

    ProfileEntry(const char* name)
        : m_Duration{ 0 },/* m_Children{},*/ m_Name{name} {}
};

class ProfileManager
{
private:
    Array<ProfileEntry> m_Stack;
    uint32_t m_TabCounter;
public:
    ProfileManager() : m_TabCounter{ 0 }{}

    void BeginProfile(const char* name) 
    {
        ProfileEntry entry(name);
        m_Stack.pushBack(entry);
        ++m_TabCounter;
    }

    void EndProfile(const char* name, float time)
    {
        uint32_t size = m_Stack.size();
        for (uint32_t i = 0; i < size; ++i)
        {
            if (m_Stack[i].m_Name == name)
                m_Stack[i].m_Duration = time;
        }
    }

    void PrintProfile()
    {
        uint32_t tabCount = m_TabCounter;
        while (tabCount > 0)
            logmsg("    ");
        uint32_t size = m_Stack.size();
        for (uint32_t i = 0; i < size; ++i)
        {
            ProfileEntry e = m_Stack[i];
            logmsg("%s -> %.2f ms\n", e.m_Name, e.m_Duration);
        }
    }
};

static ProfileManager gs_ProfileManager;

struct ProfileTimer
{
    Stopwatch m_Stopwatch;
    const char* m_Name;

    ProfileTimer(const char* name)
    {
        m_Name = name;
        gs_ProfileManager.BeginProfile(name);
    }
    ~ProfileTimer()
    {
        m_Stopwatch.stop();
        float elapsedTime = m_Stopwatch.getDurationMs();
        gs_ProfileManager.EndProfile(m_Name, elapsedTime);
    }
};

