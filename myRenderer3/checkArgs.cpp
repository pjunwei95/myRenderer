#include "checkArgs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "config.txt"

//void function()
//{
//    FILE *pfin;
//    if ((pfin = fopen(FILENAME, "r")) == NULL)
//    {
//        printf("Error opening data file %s\n", FILENAME);
//        exit(EXIT_FAILURE); //shutdown program
//    }
//}


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
        printf("string[%d] is \"%s\"\n", i, string);

        /*if (strcmp(string, "int") == 0)
            printf("This works\n");*/
    }

    //function();
    return 0;
}