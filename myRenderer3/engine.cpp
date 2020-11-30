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
void Engine::InitGlobals()
{
    SetSystemFrequency();
    g_IsDone = false;
    g_Mode = Engine::Mode::MAIN;
    g_Option = Engine::Option::NORMAL;
}

#endif