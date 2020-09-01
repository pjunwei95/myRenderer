#include "isValidArgs.h"
#include <stdio.h>
#include <string.h>
#include "fileManager.h"

int isValidArgs(int argc, char *argsv[])
{
    if (argc < 2) 
    {
        printf("ERROR: You need at least one argument.\n");
        printf("Usage: ./app.exe (int)numArgs (string)args\n");
        return 0;
    }

    // Examples
    // app.exe 2 debug
    // app.exe 4 test hi int

    //check args
    if (argc == 3 && (strcmp(argsv[2], "config") == 0)) // app.exe 2 config
    {
        printf("Loading default configurations\n");
        return 1;
    }
    else //else default reading
    {
        for (int i = 0; i < argc; ++i)
        {
            // string is address of first element of string
            // argsv is pointer to char pointer
            char *string = argsv[i];
            printf("string[%d] is \"%s\"\n", i, string);

            if (strcmp(string, "config") == 0)
                printf("This works\n");
        }
    }
    return 0;
}