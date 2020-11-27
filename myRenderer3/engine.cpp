#include "engine.h"

static bool g_IsDone;
EngineMode g_Mode;
EngineOption g_Option;


void InitGlobals()
{
    setSystemFrequency();
    g_IsDone = false;
    g_Mode = EngineMode::MAIN;
    g_Option = EngineOption::NORMAL;
}

EngineMode& GetMode()
{
    return g_Mode;
}

void SetMode(EngineMode mode)
{
    g_Mode = mode;
}

void SetOption(EngineOption option)
{
    g_Option = option;
}

EngineOption& GetOption()
{
    return g_Option;
}



void setIsDone(bool value) { g_IsDone = value; }

bool getIsDone() { return g_IsDone; }