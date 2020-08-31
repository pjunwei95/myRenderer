#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>


#define TEMP_MAX_CHAR 256

#define LOGNAME "debug.log"

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
        printf("-------------Reading File \"%s\"-------------\n", fileName);
        fseek(stream, 0L, SEEK_SET);
        char arguments[TEMP_MAX_CHAR];
        if (fscanf_s(stream, "%s", arguments, TEMP_MAX_CHAR) == 1)
        {
            printf("Stream read, the input is \"%s\"\n", arguments);
        }
        // config.txt
        /*
            debug
        */
        printf("-------------Closing File \"%s\"-------------\n", fileName);
        fclose(stream);
    }
}