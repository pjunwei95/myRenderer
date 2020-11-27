#include "engine.h"

#ifdef ENGINECLASS
void Engine::InitGlobals()
{
    setSystemFrequency();
    g_IsDone = false;
    g_Mode = EngineMode::MAIN;
    g_Option = EngineOption::NORMAL;
}

Engine::EngineMode& Engine::GetMode() { return g_Mode; }
void Engine::SetMode(EngineMode mode) { g_Mode = mode; }

Engine::EngineOption& Engine::GetOption() { return g_Option; }
void Engine::SetOption(EngineOption option) { g_Option = option; }

bool Engine::getIsDone() { return g_IsDone; }
void Engine::setIsDone(bool value) { g_IsDone = value; }


//to be called only once. not per frame
void Engine::setSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }
Timer Engine::getSystemFrequency() { return g_Frequency; }

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