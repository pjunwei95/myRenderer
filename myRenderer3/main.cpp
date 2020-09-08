//#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <stdio.h>

#include "engine.h"
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "logger.h"
#include "profiler.h"

BOOL isDone;

int main(int argc, char *argsv[])
{

    openLogStream();

    testProfiling();

    processArgs(argc, argsv);

    setIsDone(FALSE);
    
    printf("Press ESC to exit the application\n");

	runMainLoop();

    closeLogStream();

	return 0;
}


void setIsDone(BOOL value)
{
    isDone = value;
}

BOOL getIsDone()
{
    return isDone;
}

