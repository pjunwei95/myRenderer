#pragma once
#include <Windows.h>
#include "stopwatch.h"

#define FPS 30

//#define ENABLE_DEBUG
#if ENABLE_DEBUG
#define DEBUG_ASSERT //for main open console windows on startup
#define BREAKPOINT_ENABLED
#endif

//Screen dimension constants
const int SCREEN_WIDTH = 800; //640
const int SCREEN_HEIGHT = 600; //480

#define ENGINECLASS
#ifdef ENGINECLASS
class Engine
{
public:
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

    void InitGlobals();

    EngineMode& GetMode();
    void SetMode(EngineMode mode);

    EngineOption& GetOption();
    void SetOption(EngineOption option);

    bool getIsDone();
    void setIsDone(bool value);

    Stopwatch::Timer getSystemFrequency();
    void setSystemFrequency();

    static Engine& Instance() 
    {
        static Engine instance;
        return instance;
    }

private:
    static Engine* ms_Instance;
    bool g_IsDone;
    Stopwatch::Timer g_Frequency;
    EngineMode g_Mode;
    EngineOption g_Option;
};
#else
typedef LARGE_INTEGER Timer;

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

void InitGlobals();

EngineMode& GetMode();
void SetMode(EngineMode mode);


EngineOption& GetOption();
void SetOption(EngineOption option);

void setIsDone(bool value);

bool getIsDone();

void setSystemFrequency();

Timer getSystemFrequency();
#endif
