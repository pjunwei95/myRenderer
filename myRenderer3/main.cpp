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
#endif


#define FILE_NAME "debug.txt"

Timer g_Frequency;

int main(int argc, char *argsv[])
{
    openLogStream(FILE_NAME);

    setGlobals();

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    if (GetMode() == EngineMode::UNIT_TEST)
    {
        runTest();
    }
    else
    {
        if (!getIsDone())
            runMainLoop();
    }

    closeLogStream();

	return 0;
}

//to be called only once. not per frame
void setSystemFrequency() { QueryPerformanceFrequency(&g_Frequency); }

Timer getSystemFrequency() { return g_Frequency; }

