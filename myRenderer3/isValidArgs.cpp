#include "isValidArgs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "config.txt"

void readFromFile(const char* fileName)
{
    FILE *stream;
    errno_t err = fopen_s(&stream, fileName, "r");

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        exit(EXIT_FAILURE); //shutdown program
    }
    else
    {
        printf("//////////Reading File \"%s\"/////////////\n", fileName);
        fseek(stream, 0L, SEEK_SET);
        char arguments[256];
        if (fscanf_s(stream, "%s", arguments, 256) == 1)
        {
            printf("stream read, the input is \"%s\"\n", arguments);
        }
        // config.txt
        /*
            debug
        */
        printf("//////////Closing File \"%s\"/////////////\n", fileName);

        fclose(stream);
    }
}


int isValidArgs(int argc, char *argsv[])
{
    if (argc < 2) 
    {
        printf("ERROR: You need at least one argument.\n");
        fprintf(stderr, "Usage: ./app.exe (int)numArgs (string)args\n");
        return 0;
    }

    // Examples
    // app.exe 2 debug
    // app.exe 4 test hi int

    //check args
    if (argc == 3 && (strcmp(argsv[2], "config") == 0)) // app.exe 2 config
    {
        printf("Setting default configurations\n");
        readFromFile(FILENAME);
    }
    else //else default reading
    {
        for (int i = 0; i < argc; ++i)
        {
            // string is address of first element of string
            // argsv is pointer to char pointer
            char *string = argsv[i];
            printf("string[%d] is \"%s\"\n", i, string);

            /*if (strcmp(string, "int") == 0)
                printf("This works\n");*/
        }
    }
    

    return 1;
}