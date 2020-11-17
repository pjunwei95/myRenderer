#include <assert.h>
#include "profileManager.h"
#include "logger.h"

//=========================================================
// Scoped Timers
ProfileTimer::ProfileTimer(const char* name)
    :m_Name{ name }
{
    ProfileManager::Instance().BeginProfile(name);
}

ProfileTimer::~ProfileTimer()
{
    float elapsedTime = m_Stopwatch.getDurationMs();
    ProfileManager::Instance().EndProfile(m_Name, elapsedTime);
}

//=========================================================
//ProfileManager

ProfileManager* ProfileManager::ms_Instance = nullptr;

ProfileManager::ProfileManager()
    : m_Stack{ }, m_TabCounter{ -1 }, m_Buffer{ 3 }
{
    //ms_Instance = this;
}

ProfileManager& ProfileManager::Instance()
{
    static ProfileManager instance;
    return instance;
}

void ProfileManager::BeginProfile(const char* name)
{
    ++m_TabCounter;
    m_Stack.pushBack(ProfileEntry{ name });
}

void ProfileManager::EndProfile(const char* name, float time)
{
    //ProfileEntry& entry = m_Stack.popBack();
    //assert(strcmp(entry.m_Name, name) == 0);
    //entry.m_Duration = time;
    //entry.m_Tab = m_TabCounter;

    bool found = false;
    uint32_t size = m_Stack.size();
    for (uint32_t i = 0; i < size; ++i)
    {
        //TODO buggy addition, it will add to the first occurence when theres multiple same profiling
        if (strcmp(m_Stack[i].m_Name, name) == 0)
        {
            m_Stack[i].m_Duration = time;
            m_Stack[i].m_Tab = m_TabCounter;
            found = true;
            break;
        }
    }
    assert(found);
    --m_TabCounter;
}

void ProfileManager::PrintProfileEntries(const Array<ProfileEntry>& stack)
{
    uint32_t size = stack.size();
    for (uint32_t i = 0; i < size; ++i)
    {
        const ProfileEntry& e = stack[i];
        uint32_t numTabs = e.m_Tab;
        while (numTabs-- > 0)
            logfile("    ");
        logfile("%s -> %.2f ms\n", e.m_Name, e.m_Duration);
        //assert(e.m_Duration > 0.01);
    }
}

void ProfileManager::PrintBufferProfile()
{
    uint32_t size = m_Buffer.size();
    uint32_t front = m_Buffer.frontIndex();
    for (uint32_t i = 0; i < size; ++i)
    {
        uint32_t idx = (front + i) % m_Buffer.capacity();
        const Array<ProfileEntry>& stack = m_Buffer.at(idx);
        logfile("#%i:\n", i + 1);
        //logmsg("(size = %i, front = %i, back = %i)\n", size, front, back);
        PrintProfileEntries(stack);
    }
}

void ProfileManager::ClearStack()
{
    m_Stack.clear();
    m_TabCounter = -1;
}

void ProfileManager::OnProfileFlip()
{
    m_Buffer.specialPushBack(m_Stack);
    ClearStack();
}

