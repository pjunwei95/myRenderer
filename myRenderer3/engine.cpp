#include "engine.h"

static bool g_IsDone;
EngineMode g_Mode;
EngineOption g_Option;


void setGlobals()
{
    setSystemFrequency();
    setIsDone(false);
    g_Mode = EngineMode::MAIN;
    g_Option = NORMAL;
}

EngineMode& GetMode()
{
    return g_Mode;
}

void SetMode(EngineMode mode)
{
    g_Mode = mode;
}



void setIsDone(bool value) { g_IsDone = value; }

bool getIsDone() { return g_IsDone; }