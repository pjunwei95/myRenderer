#pragma once
#include <assert.h>
#include "stopwatch.h"
#include "array.h"
#include "logger.h"

#define MAX_CHAR 320

struct ProfileEntry
{
    ProfileEntry(const char* name)
        : m_Duration{ 0 }, m_Children{}, m_Name{}
    {
        strcpy_s(m_Name, MAX_CHAR, name);
    }

    ~ProfileEntry()
    {
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

    void RegisterProfileEntry()
    {
    }


private:
    Array<ProfileEntry*> stack;
};

static ProfileManager gs_ProfileManager;
