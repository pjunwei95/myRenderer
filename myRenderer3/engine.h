#pragma once
#include <Windows.h>
#include "stopwatch.h"

#define FPS 30

#define ENABLE_DEBUG
#ifdef ENABLE_DEBUG
//#define DEBUG_ASSERT //for debugging asserts by opening console window messages
#define BREAKPOINT_ENABLED //for enabling breakpoints on release
#endif

//Screen dimension constants
const int SCREEN_WIDTH = 800; //640
const int SCREEN_HEIGHT = 600; //480

#define ENGINECLASS
#ifdef ENGINECLASS
class Engine
{
public:
    enum class Mode
    {
        MAIN,
        UNIT_TEST
    };

    enum class Option
    {
        NORMAL,
        DEBUG
    };

    static Engine& Instance();
    void InitGlobals();

    inline Mode& GetMode() { return g_Mode; }
    inline void SetMode(Mode mode) { g_Mode = mode; }

    inline Option& GetOption() { return g_Option; }
    inline void SetOption(Option option) { g_Option = option; }

    inline bool GetIsDone() { return g_IsDone; }
    inline void SetIsDone(bool value) { g_IsDone = value; }

    //to be called only once. not per frame
    inline void SetSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }
    inline Stopwatch::Timer GetSystemFrequency() { return g_Frequency; }


private:
    static Engine* ms_Instance;
    bool g_IsDone;
    Stopwatch::Timer g_Frequency;
    Mode g_Mode;
    Option g_Option;
};
#else
namespace Engine
{
    enum class Mode
    {
        MAIN,
        UNIT_TEST
    };

    enum class Option
    {
        NORMAL,
        DEBUG
    };

    void InitGlobals();

    inline Mode& GetMode() { return g_Mode; }
    inline void SetMode(Mode mode) { g_Mode = mode; }

    inline Option& GetOption() { return g_Option; }
    inline void SetOption(Option option) { g_Option = option; }

    inline bool GetIsDone() { return g_IsDone; }
    inline void SetIsDone(bool value) { g_IsDone = value; }

    //to be called only once. not per frame
    inline void SetSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }
    inline Stopwatch::Timer GetSystemFrequency() { return g_Frequency; }

    bool g_IsDone;
    Stopwatch::Timer g_Frequency;
    Mode g_Mode;
    Option g_Option;
};
#endif
