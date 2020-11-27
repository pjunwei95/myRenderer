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


int main(int argc, char *argsv[])
{
    openLogStream(FILE_NAME);

    //InitGlobals();
    Engine::Instance().InitGlobals();

    processArgs(argc, argsv);
    
    //printf("Press ESC to exit the application\n");
    //if (GetMode() == EngineMode::UNIT_TEST)
    if (Engine::Instance().GetMode() == Engine::EngineMode::UNIT_TEST)
    {
        ExecuteAllTests();
    }
    else
    {
        //if (!getIsDone())
        if (!Engine::Instance().getIsDone())
            runMainLoop();
    }

    closeLogStream();

	return 0;
}
