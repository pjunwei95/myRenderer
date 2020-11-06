//#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <stdio.h>
#include "engine.h"
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "logger.h"

#ifndef DEBUG_ASSERT
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

bool g_IsDone;
Timer g_Frequency;

int main(int argc, char *argsv[])
{
    openLogStream();

    setGlobals();

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    if (!g_IsDone)
	    runMainLoop();

    closeLogStream();

	return 0;
}

void setGlobals()
{
    setSystemFrequency();
    setIsDone(false);
}

void setIsDone(bool value)
{
    g_IsDone = value;
}

bool getIsDone()
{
    return g_IsDone;
}

void setSystemFrequency()
{
    QueryPerformanceFrequency(&g_Frequency); //to be called only once. not per frame
}

Timer getSystemFrequency()
{
    return g_Frequency;
}

