#include <assert.h>
#include "profileManager.h"
#include "logger.h"

ProfileManager gs_ProfileManager;

//=========================================================
//ProfileManager

void ProfileManager::BeginProfile(const char* name)
{
    ++m_TabCounter;
    ProfileEntry entry(name);
    m_Stack.pushBack(entry);
}

void ProfileManager::EndProfile(const char* name, float time)
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

void ProfileManager::PrintProfileEntries(const Array<ProfileEntry>& stack)
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

void ProfileManager::PrintBufferProfile()
{
    auto size = m_Buffer.size();
    auto front = m_Buffer.frontIndex();
    for (auto i = 0u; i < size; ++i)
    {
        auto idx = (front + i) % m_Buffer.capacity();
        Array<ProfileEntry> stack = m_Buffer.at(idx);
        logmsg("Frame #%i:\n", i + 1);
        //logmsg("(size = %i, front = %i, back = %i)\n", size, front, back);
        PrintProfileEntries(stack);
    }
}
//=========================================================
// Scoped Timers
ProfileTimer::ProfileTimer(const char* name)
    :m_Name{ name }
{
    gs_ProfileManager.BeginProfile(name);
}

ProfileTimer::~ProfileTimer()
{
    float elapsedTime = m_Stopwatch.getDurationMs();
    gs_ProfileManager.EndProfile(m_Name, elapsedTime);
}


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
    float elapsedTime = (float)stopTime.QuadPart / 1000;
    gs_ProfileManager.EndProfile(nameToFind, elapsedTime);
}