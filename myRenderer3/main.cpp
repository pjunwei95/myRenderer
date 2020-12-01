//#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include "processArgs.h"
#include "runMainLoop.h"
#include "fileManager.h"
#include "runTest.h"

#ifndef DEBUG_ASSERT
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define FILE_NAME "debug.txt"
//TODO your profiler is still dumping to the default "debug.txt".dump it to a separate file

int main(int argc, char *argsv[])
{
    OpenLogStream(FILE_NAME);

    Engine::Instance().InitGlobals();

    ProcessArgs(argc, argsv);
    
    if (Engine::Instance().GetMode() == Engine::Mode::UNIT_TEST)
    {
        ExecuteAllTests();
    }
    else
    {
        if (!Engine::Instance().GetIsDone())
            RunMainLoop();
    }

    CloseLogStream();

	return 0;
}
