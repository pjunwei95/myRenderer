#pragma once
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"

#define CONCAT(x,y) x##y
#define MACRO_CONCAT(x,y) CONCAT(x, y)

#define PROFILE_MACRO 1

#if PROFILE_MACRO
#define PROFILE_FUNCTION() ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(__FUNCTION__)
#define PROFILE_SCOPED(name) ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(#name)

#define PROFILE_BEGIN(name) Stopwatch::Timer* name = GetStartTime(#name)
#define PROFILE_END(name) LapTimer(#name, name) 
#else
#define PROFILE_BEGIN(name)
#define PROFILE_END(name) 
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION()
#endif

struct ProfileEntry
{
    const char* m_Name;
    uint32_t m_Tab;
    float m_Duration;

    ProfileEntry():m_Duration{0}, m_Name{nullptr}, m_Tab{0}{}

    ProfileEntry(const char* name)
        : m_Name{ name }, m_Duration{ 0 }, m_Tab{ 0 }{}
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
    void PrintStackProfile() { PrintProfileEntries(m_Stack); }
    void clearBuffer() { m_Buffer.clear(); }
    void clearStack()
    {
        m_Stack.clear();
        m_TabCounter = -1;
    }
    void OnProfileFlip()
    {
        m_Buffer.specialPushBack(m_Stack);
        clearStack();
    }

    void BeginProfile(const char* name);
    void EndProfile(const char* name, float time);
    void PrintProfileEntries(const Array<ProfileEntry>& stack);
    void PrintBufferProfile();
};

extern ProfileManager gs_ProfileManager;

//=========================================================
//Scoped Timers

class ProfileTimer
{
private:
    Stopwatch m_Stopwatch;
    const char* m_Name;
public:
    ProfileTimer(const char* name);
    ~ProfileTimer();
};

//=========================================================
//Non-scoped Timers
Stopwatch::Timer* GetStartTime(const char* name);

void LapTimer(const char* nameToFind, Stopwatch::Timer* startTime);