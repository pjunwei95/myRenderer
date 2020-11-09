#pragma once
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"

#define CONCAT(x,y) x##y
#define MACRO_CONCAT(x,y) CONCAT(x, y)

#define PROFILE_MACRO 0

#if PROFILE_MACRO
#define PROFILE_FUNCTION() ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(__FUNCTION__)
#define PROFILE_SCOPED(name) ProfileTimer MACRO_CONCAT(timer, __COUNTER__)(#name)

#define PROFILE_BEGIN(name) \
    Stopwatch MACRO_CONCAT(timer, __COUNTER__); \
    ProfileEntry __profileEntry__##name__(name); \
    ProfileManager::Instance().m_Stack.pushBack(__profileEntry__##name__);

#define PROFILE_END(name) LapTimer(#name, name) 

#else
#define PROFILE_BEGIN(name) (void(0))
#define PROFILE_END(name) 
#define PROFILE_SCOPED(name)
#define PROFILE_FUNCTION()
#endif

//for (...)
//    PROFILE_FUNCTION();
//int i = 0;
//i = 5;

struct ProfileEntry
{
    const char* m_Name = nullptr;
    uint32_t m_Tab = 0;
    float m_Duration = 1000000;

    ProfileEntry(const char* name = nullptr)
        : m_Name{ name }{}
};

class ProfileManager
{
private:
    static ProfileManager* ms_Instance;
    Array<ProfileEntry> m_Stack;
    int m_TabCounter;
    CircularBuffer<Array<ProfileEntry>> m_Buffer;
    ProfileManager() : m_TabCounter{ -1 }, m_Buffer{ 3 }
    {
        ms_Instance = this;
    }
public:
    static ProfileManager& Instance()
    {
        static ProfileManager pm;
        return pm;
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