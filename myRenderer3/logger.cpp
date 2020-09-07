#include "fileManager.h"
#include "logger.h"

//#include <vector>
//#include <cstdio>
//#include <cstdarg>
#include "stdarg.h"

#define FILE_NAME "debug.txt"

FileHandle fileHandle;

void logmsg(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    printf(buffer);
    vfprintf(fileHandle, format, args);
    va_end(args);
}

void openLogStream()
{
    //check if file is there
    openFile(FILE_NAME, TYPE_TEXT, MODE_WRITE, &fileHandle);
    fprintf(fileHandle, "===========Logging Begin===========\n");
    //closeFile(fileHandle);
}

void closeLogStream()
{

    //openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    fprintf(fileHandle, "===========Logging End=============\n");
    closeFile(fileHandle);
}
