#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
//#include <windows.h>
#include <stdio.h>

#include "engine.h"
#include "isValidArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"

BOOL isDone;

int main(int argc, char *argsv[])
{

    setIsDone(FALSE);

    printf("Press ESC to exit the application\n");
    
    //printf("isDone value is now %d\n", getIsDone());

    if (isValidArgs(argc, argsv))

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
