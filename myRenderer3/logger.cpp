#include "fileManager.h"
#include "logger.h"

#define FILE_NAME "debug.txt"

void logmsg(const char * msg)
{
    FileHandle fileHandle;

    openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    //write output to file
    //fprintf(fileHandle, "===========Logging Begin===========\n");
    fprintf(fileHandle, msg);
    //fprintf(fileHandle, "===========Logging End=============\n");
    closeFile(fileHandle);
}

void beginLog()
{
    FileHandle fileHandle;

    openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    fprintf(fileHandle, "===========Logging Begin===========\n");
    closeFile(fileHandle);
}

void endLog()
{
    FileHandle fileHandle;

    openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    fprintf(fileHandle, "===========Logging End=============\n");
    closeFile(fileHandle);
}