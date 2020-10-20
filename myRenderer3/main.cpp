//#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <stdio.h>
#include "engine.h"
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "logger.h"

#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

bool isDone;
LARGE_INTEGER g_Frequency;

int main(int argc, char *argsv[])
{
    openLogStream();

    setGlobals();

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    if (!isDone)
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
    isDone = value;
}

bool getIsDone()
{
    return isDone;
}

void setSystemFrequency()
{
    QueryPerformanceFrequency(&g_Frequency); //to be called only once. not per frame
}

LARGE_INTEGER getSystemFrequency()
{
    return g_Frequency;
}

