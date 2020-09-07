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
    PROFILE_INIT();
    openLogStream();
    //PROFILE_BEGIN(main.cpp);

    testProfiling();

    processArgs(argc, argsv);

    setIsDone(FALSE);
    
    //if (!getIsDone())
        //log("isDone value is now false\n");

    printf("Press ESC to exit the application\n");

	runMainLoop();

    //PROFILE_END(main.cpp);

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

