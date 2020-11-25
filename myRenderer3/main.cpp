//#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <stdio.h>
#include "engine.h"
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "logger.h"
#include "runTest.h"

#ifndef DEBUG_ASSERT
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#   pragma optimize("", off) //for breakpoints
#endif


#define FILE_NAME "debug.txt"

bool g_IsDone;
Timer g_Frequency;
EngineMode g_Mode;

int main(int argc, char *argsv[])
{
    openLogStream(FILE_NAME);

    setGlobals();

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    if (g_Mode == EngineMode::UNIT_TEST)
    {
        runTest();
    }
    else
    {
        if (!g_IsDone)
            runMainLoop();
    }

    closeLogStream();

	return 0;
}

void setGlobals()
{
    setSystemFrequency();
    setIsDone(false);
    setMode(MAIN);
}

void setMode(EngineMode mode) { g_Mode = mode; }

void setIsDone(bool value) { g_IsDone = value; }

bool getIsDone() { return g_IsDone; }

//to be called only once. not per frame
void setSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }

Timer getSystemFrequency() { return g_Frequency; }

