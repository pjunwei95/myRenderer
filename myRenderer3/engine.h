#pragma once
#include <Windows.h>

#define FPS 30

//#if ENABLE_DEBUG
#if 1
#define DEBUG_ASSERT //for main open console windows on startup
#define ENABLE_BREAKPOINT
#endif


typedef LARGE_INTEGER Timer;

//Screen dimension constants
const int SCREEN_WIDTH = 800; //640
const int SCREEN_HEIGHT = 600; //480

enum class EngineMode
{
    MAIN,
    UNIT_TEST
};

enum class EngineOption
{
    NORMAL,
    DEBUG
};

//extern EngineMode g_Mode;
//extern EngineOption g_Option;

void InitGlobals();

EngineMode& GetMode();
void SetMode(EngineMode mode);


EngineOption& GetOption();
void SetOption(EngineOption option);

void setIsDone(bool value);

bool getIsDone();

void setSystemFrequency();

Timer getSystemFrequency();

