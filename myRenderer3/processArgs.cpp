#include "processArgs.h"
#include "fileManager.h"
#include "logger.h"

#ifdef BREAKPOINT_ENABLED
#pragma optimize("", off)
#endif
const char* smapleText = "debug\nhi";

void loadConfig()
{
    //TODO 
    //you can always assume the "config.txt" file will always be present. if not, init default values
    //logmsg("Loading default configurations\n");
    FileManager fm;

    //fm.rea
    //search if file exist
    //  if not exist, create file
    //      openfile
    //      write to file
    //      closefile
    //  if exist, read
    fm.readAndProcessFile("config.txt", FileManager::TYPE_TEXT);
}

void ProcessArgs(int argc, char *argsv[])
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
            Engine::Instance().SetMode(Engine::Mode::UNIT_TEST);
        }
        else if (0 == strcmp(string, "debug"))
        {
            //SetOption(EngineOption::DEBUG);
            Engine::Instance().SetOption(Engine::Option::DEBUG);
        }
    }
}

