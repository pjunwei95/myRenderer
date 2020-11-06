#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "logger.h"
#include "circularBuffer.h"

#define CONCAT(x,y) x##y
#define MACRO_CONCAT(x,y) CONCAT(x, y)

#define PROFILE_MACRO 1

#if PROFILE_MACRO
#define PROFILE_BEGIN(name) Stopwatch::Timer* name = GetStartTime(#name)
#define PROFILE_END(name) LapTimer(#name, name) 
#define PROFILE_SCOPED(name) ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(#name)
#define PROFILE_FUNCTION() ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(__FUNCTION__)
#else
#define PROFILE_BEGIN(name)
#define PROFILE_END(name) 
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION()
#endif

struct ProfileEntry
{
   /* Array<ProfileEntry*> m_Children;*/
    const char* m_Name;
    uint32_t m_Tab;
    float m_Duration;

    ProfileEntry():m_Duration{0}, m_Name{nullptr}, m_Tab{0}{}

    ProfileEntry(const char* name)
        : m_Name{ name }, m_Duration{ 0 },/* m_Children{},*/ m_Tab{ 0 }{}
};

class ProfileManager
{
private:
    Array<ProfileEntry> m_Stack;
    int m_TabCounter;
    CircularBuffer<Array<ProfileEntry>> m_Buffer;
public:
    ProfileManager() : m_TabCounter{ -1 }, m_Buffer{ 3 }
    {
    }

    void BeginProfile(const char* name) 
    {
        ++m_TabCounter;
        ProfileEntry entry(name);
        m_Stack.pushBack(entry);
    }

    void EndProfile(const char* name, float time)
    {
        uint32_t size = m_Stack.size();
        for (uint32_t i = 0; i < size; ++i)
            if (m_Stack[i].m_Name == name)
            {
                m_Stack[i].m_Duration = time;
                m_Stack[i].m_Tab = m_TabCounter;
            }
        --m_TabCounter;
    }

    void clearStack()
    {
        m_Stack.clear();
        m_TabCounter = -1;
    }

    void clearBuffer() { m_Buffer.clear(); }

    void PrintStackProfile()
    {
        PrintProfileEntries(m_Stack);
    }

    void PrintProfileEntries(const Array<ProfileEntry>& stack)
    {
        auto size = stack.size();
        for (uint32_t i = 0; i < size; ++i)
        {
            ProfileEntry e = m_Stack[i];
            uint32_t numTabs = e.m_Tab;
            while (numTabs-- > 0)
                logmsg("    ");
            logmsg("%s -> %.2f ms\n", e.m_Name, e.m_Duration);
        }
    }


    void PrintBufferProfile()
    {
        auto size = m_Buffer.size();
        auto front = m_Buffer.frontIndex();
        auto back = m_Buffer.backIndex();

        for (auto i = 0u; i < size; ++i)
        {
            auto idx = (front + i) % m_Buffer.capacity();
            Array<ProfileEntry> stack = m_Buffer.at(idx);
            logmsg("Frame #%i ", i);
            logmsg("(size = %i, front = %i, back = %i)\n", size, front, back);
            PrintProfileEntries(stack);
        }
    }

    void OnProfileFlip()
    {
        m_Buffer.specialPushBack(m_Stack);
        clearStack();
    }

};

static ProfileManager gs_ProfileManager;

class ProfileTimer
{
private:
    Stopwatch m_Stopwatch;
    const char* m_Name;
public:
    ProfileTimer(const char* name)
    {
        m_Name = name;
        gs_ProfileManager.BeginProfile(name);
    }

    ~ProfileTimer()
    {
        float elapsedTime = m_Stopwatch.getDurationMs();
        gs_ProfileManager.EndProfile(m_Name, elapsedTime);
    }
};

//=========================================================
//Non-scoped Timers
Stopwatch::Timer* GetStartTime(const char* name)
{
    gs_ProfileManager.BeginProfile(name);
    Stopwatch timer;
    Stopwatch::Timer* startTime = new Stopwatch::Timer;
    timer.updateTimeStamp(*startTime);
    return startTime;
}

void LapTimer(const char* nameToFind, Stopwatch::Timer* startTime)
{
    Stopwatch timer;
    Stopwatch::Timer stopTime;
    timer.updateTimeStamp(stopTime);
    stopTime.QuadPart -= startTime->QuadPart;
    delete startTime;
    stopTime.QuadPart *= 1000000;
    stopTime.QuadPart /= getSystemFrequency().QuadPart;
    float elapsedTime = (float) stopTime.QuadPart / 1000;
    gs_ProfileManager.EndProfile(nameToFind, elapsedTime);
}