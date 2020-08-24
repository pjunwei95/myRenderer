#include "checkArgs.h"
#include <stdio.h>

int checkArgs(int argc, char *argsv[])
{
    if (argc < 2) {
        printf("ERROR: You need at least one argument.\n");
        return 1;
    }

    for (int i = 0; i < argc; ++i)
    {
        // string is address of first element of string
        // argsv is pointer to char pointer
        char *string = argsv[i];
        printf("string is \"%s\"\n", string);
    }
    return 0;
}