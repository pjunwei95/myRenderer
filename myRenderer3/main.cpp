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

int main(int argc, char *argsv[])
{
    openLogStream();

    setIsDone(false);

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    if (!isDone)
	    runMainLoop();

    closeLogStream();

	return 0;
}

void setIsDone(bool value)
{
    isDone = value;
}

bool getIsDone()
{
    return isDone;
}

