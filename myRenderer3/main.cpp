#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
//#include <windows.h>
#include <stdio.h>

#include "engine.h"
#include "isValidArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"

BOOL isDone;


FILE *pfout;

int main(int argc, char *argsv[])
{

    setIsDone(FALSE);

    //printf("isDone value is now %d\n", getIsDone() );
    printf("Press ESC to exit the application\n");
    
    pfout = startLog(pfout);

    if (isValidArgs(argc, argsv))
    {
        //start logging

        //how to end logging? use a global bool to keep track?
    }

	runMainLoop();
    endLog(pfout);


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
