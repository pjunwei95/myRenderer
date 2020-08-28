#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <windows.h>
#include <stdio.h>

#include "engine.h"
#include "checkArgs.h"
#include "runMainLoop.h"

BOOL isDone;

int main(int argc, char *argsv[])
{
    setIsDone(FALSE);

    printf("isDone value is now %d\n", getIsDone() );

    checkArgs(argc, argsv);

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
