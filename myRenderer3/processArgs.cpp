#include "processArgs.h"
#include <stdio.h>
#include <string.h>
#include "fileManager.h"

void processArgs(int argc, char *argsv[])
{
    if (argc < 2) 
    {
        printf("No external arguments.\n");
        printf("Usage: ./app.exe (int)numArgs (string)args\n");
    }

    // Examples
    // app.exe 2 debug
    // app.exe 4 test hi int
    
    //check args
    for (int i = 0; i < argc; ++i)
    {
        // string is address of first element of string
        // argsv is pointer to char pointer
        char *string = argsv[i];
        printf("string[%d] is \"%s\"\n", i, string);
    }
    
}

