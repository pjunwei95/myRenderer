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

//=========================================================
//ProfileInfo

ProfileInfo& ProfileInfo::Instance()
{
    static ProfileInfo instance;
    return instance;
}

void ProfileInfo::DumpProfileInfo()
{
    PreprocessNameList();
    PrintProfileInfo();
    ClearNameList();
}

void ProfileInfo::PrintProfileInfo()
{
    const CircularBuffer<Array<ProfileEntry>>& buffer = ProfileManager::Instance().GetBuffer();
    for (uint32_t i = 0; i < m_NameList.size(); ++i)
    {
        const char* name = m_NameList[i];
        int count = 0;
        float total = 0.0;
        float max = 0.0;
        for (uint32_t j = 0; j < buffer.size(); ++j)
        {
            const Array<ProfileEntry>& stack = buffer.at(j);
            for (uint32_t k = 0; k < stack.size(); ++k)
            {
                if (strcmp(name, stack[k].m_Name) == 0)
                {
                    ++count;
                    float time = stack[k].m_Duration;
                    total += time;
                    if (time > max)
                        max = time;
                }
            }
        }
        logfile("\nProfile Tag: %s\nAvg per frame: %.2f ms\nTotal for all %i frames: %.2f ms\nHighest Spike: %.2f ms\n", name, total / count, count, total, max);
    }
}

void ProfileInfo::PreprocessNameList()
{
    const CircularBuffer<Array<ProfileEntry>>& buffer = ProfileManager::Instance().GetBuffer();
    for (uint32_t i = 0; i < buffer.size(); ++i)
    {
        const Array<ProfileEntry>& stack = buffer.at(i);
        for (uint32_t j = 0; j < stack.size(); ++j)
        {
            const char* name = stack[j].m_Name;
            if (this->contains(name)) //skip
                continue;
            else
                m_NameList.pushBack(name);
        }
    }
}

bool ProfileInfo::contains(const char* name)
{
    for (uint32_t i = 0; i < m_NameList.size(); ++i)
    {
        if (strcmp(m_NameList[i], name) == 0)
            return true;
    }
    return false;
}


