#include "processArgs.h"
#include <stdio.h>
#include <string.h>
#include "fileManager.h"
#include "logger.h"
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

        if (0 == strcmp(string, "test"))
        {
            //SetMode(EngineMode::UNIT_TEST);
            Engine::Instance().SetMode(Engine::EngineMode::UNIT_TEST);
        }
        else if (0 == strcmp(string, "debug"))
        {
            //SetOption(EngineOption::DEBUG);
            Engine::Instance().SetOption(Engine::EngineOption::DEBUG);
        }
    }
}

