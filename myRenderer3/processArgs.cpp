#include "processArgs.h"
#include <stdio.h>
#include <string.h>
#include "fileManager.h"
#include "logger.h"
#include "runTest.h"
#include "engine.h"

void loadConfig()
{
    //TODO 
    //you can always assume the "config.txt" file will always be present. if not, init default values
    FileManager fm;

    //logmsg("Loading default configurations\n");

    fm.readAndProcessFile("config.txt", FileManager::TYPE_TEXT);
}

void processArgs(int argc, char *argsv[])
{
    if (argc < 2) 
    {
        logmsg("No external arguments.\n");
        logmsg("Usage: ./app.exe (int)numArgs (string)args\n");
    }

    loadConfig();

    //check args
    for (int i = 0; i < argc; ++i)
    {
        char *string = argsv[i];
        //logmsg("argsv[%d] is \"%s\"\n", i, string);
        if (0 == strcmp(string, "test"))
        {
            runTest();
            //exit(EXIT_SUCCESS);
            setIsDone(true);
        }
    }
}
