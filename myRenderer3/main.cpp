#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
//#include <windows.h>
#include <stdio.h>

#include "engine.h"
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "logger.h"

BOOL isDone;

int main(int argc, char *argsv[])
{
    processArgs(argc, argsv);

    setIsDone(FALSE);
    
    //if (!getIsDone())
        //log("isDone value is now false\n");

    loadConfig();

    printf("Press ESC to exit the application\n");

	runMainLoop();
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
