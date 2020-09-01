#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>


#define TEMP_MAX_CHAR 256
#define LOGNAME "debug.log"

FILE *pfout;


//bool OpenFile(const char* FileName, OpenType openType, FileHandle fileHandle)



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
        //TODO: Handle multiple inputs
        if (fscanf_s(stream, "%s", arguments, TEMP_MAX_CHAR) == 1)
        {
            printf("Stream read, the input is \"%s\"\n", arguments);
        }
        // config.txt
        /*
            debug
            arg2
            arg3
        */
        printf("-------------Closing File \"%s\"-------------\n", fileName);
        fclose(stream);
    }
}

FILE* startLog()
{
    const char* fileName = LOGNAME;
    /* open output file */

    //check whether is overwriting
    errno_t err = fopen_s(&pfout, fileName, "a");

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        printf("Cannot write to log\n");
        //dont shutdown at every logging
    }
    else
    {
        fprintf(pfout, "===========Logging Begin===========\n");
    }

    return pfout;
}

void endLog(FILE* pf)
{
    fprintf(pf, "===========Logging End===========\n");

    fclose(pf);
}
