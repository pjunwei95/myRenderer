#pragma once
#include "stopwatch.h"
#include "array.h"
#include "circularBuffer.h"

#define CONCAT(x,y) x##y
#define MACRO_CONCAT(x,y) CONCAT(x, y)
#define UNIQUENAME() MACRO_CONCAT(__func__, __COUNTER__)

#define PROFILE_MACRO 1
// Roger's style for PROFILE_BEGIN(name)
//Stopwatch MACRO_CONCAT(__timer__, __COUNTER__); \
//ProfileManager::Instance().GetStack.pushBack(ProfileEntry{ #name });

#if PROFILE_MACRO
#define PROFILE_FUNCTION() ProfileTimer MACRO_CONCAT(__timer__, __COUNTER__)(__func__)
#define PROFILE_SCOPED(name) ProfileTimer MACRO_CONCAT(__timer__, __COUNTER__)(#name)
#define PROFILE_BEGIN(name) \
    Stopwatch __timer__##name; \
    ProfileManager::Instance().BeginProfile(#name)

#define PROFILE_END(name) \
    float __duration__##name = __timer__##name.getDurationMs();\
    ProfileManager::Instance().EndProfile(#name, __duration__##name)
#else
#define PROFILE_BEGIN(name) (void(0))
#define PROFILE_END(name) (void(0))
#define PROFILE_SCOPED(name) (void(0))
#define PROFILE_FUNCTION() (void(0))
#endif

//for (...)
//    PROFILE_FUNCTION();
//int i = 0;
//i = 5;

//=========================================================
//Profile Entry

struct ProfileEntry
{
    const char* m_Name = nullptr;
    uint32_t m_Tab = 0;
    float m_Duration = -1;

    ProfileEntry(const char* name = nullptr)
        : m_Name{ name }
    {
    }
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
//Profile Manager

class ProfileManager
{
private:
    ProfileManager();

    static ProfileManager* ms_Instance;
    Array<ProfileEntry> m_Stack;
    int m_TabCounter;
    CircularBuffer<Array<ProfileEntry>> m_Buffer;
public:
    static ProfileManager& Instance();
    void BeginProfile(const char* name);
    void EndProfile(const char* name, float time);
    void PrintProfileEntries(const Array<ProfileEntry>& stack);
    void PrintBufferProfile();
    void ClearStack();
    void OnProfileFlip();

    void ClearBuffer() { m_Buffer.clear(); }
    void PrintStackProfile() { PrintProfileEntries(m_Stack); }
    Array<ProfileEntry>& GetStack() { return m_Stack; }
};

//=========================================================
//Non-scoped Timers (Deprecated)
//Stopwatch::Timer* GetStartTime(const char* name)
//{
//    ProfileManager::Instance().BeginProfile(name);
//    Stopwatch timer;
//    Stopwatch::Timer* startTime = new Stopwatch::Timer;
//    timer.updateTimeStamp(*startTime);
//    return startTime;
//}
//
//void LapTimer(const char* nameToFind, Stopwatch::Timer* startTime)
//{
//    Stopwatch timer;
//    Stopwatch::Timer stopTime;
//    timer.updateTimeStamp(stopTime);
//    stopTime.QuadPart -= startTime->QuadPart;
//    delete startTime;
//    stopTime.QuadPart *= 1000000;
//    stopTime.QuadPart /= getSystemFrequency().QuadPart;
//    float elapsedTime = (float)stopTime.QuadPart / 1000;
//    ProfileManager::Instance().EndProfile(nameToFind, elapsedTime);
//}