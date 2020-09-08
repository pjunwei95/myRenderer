#include "processArgs.h"
#include <stdio.h>
#include <string.h>
#include "fileManager.h"
#include "logger.h"

void loadConfig()
{
    //TODO 
    //you can always assume the "config.txt" file will always be present. if not, init default values

    logmsg("Loading default configurations\n");

    readAndProcessFile("config.txt", TYPE_TEXT);
}

void processArgs(int argc, char *argsv[])
{
    if (argc < 2) 
    {
        logmsg("No external arguments.\n");
        logmsg("Usage: ./app.exe (int)numArgs (string)args\n");
    }

    //check args
    for (int i = 0; i < argc; ++i)
    {
        // string is address of first element of string
        // argsv is pointer to char pointer
        char *string = argsv[i];
        logmsg("argsv[%d] is \"%s\"\n", i, string);
    }
    loadConfig();
}
