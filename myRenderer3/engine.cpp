#include "engine.h"

#ifdef ENGINECLASS
void Engine::InitGlobals()
{
    SetSystemFrequency();
    g_IsDone = false;
    g_Mode = Engine::Mode::MAIN;
    g_Option = Engine::Option::NORMAL;
}

Engine& Engine::Instance()
{
    static Engine instance;
    return instance;
}

#else

static bool g_IsDone;
Timer g_Frequency;
EngineMode g_Mode;
EngineOption g_Option;


void InitGlobals()
{
    setSystemFrequency();
    g_IsDone = false;
    g_Mode = EngineMode::MAIN;
    g_Option = EngineOption::NORMAL;
}

EngineMode& GetMode() { return g_Mode; }
void SetMode(EngineMode mode) { g_Mode = mode; }

EngineOption& GetOption() { return g_Option; }
void SetOption(EngineOption option) { g_Option = option; }

bool getIsDone() { return g_IsDone; }
void setIsDone(bool value) { g_IsDone = value; }


//to be called only once. not per frame
void setSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }
Timer getSystemFrequency() { return g_Frequency; }

#endif