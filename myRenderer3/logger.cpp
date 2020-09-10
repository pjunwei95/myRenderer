#include "fileManager.h"
#include "logger.h"
#include <stdarg.h>
#include <cassert>
#include <string.h>

#define FILE_NAME "debug.txt"
#define CHAR_MAX_LIMIT 256

FileHandle fileHandle;

void logmsg(const char *format, ...)
{
    assert(format); //check if null

    char buffer[CHAR_MAX_LIMIT];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, CHAR_MAX_LIMIT, format, args);

    assert(vsnprintf(buffer, CHAR_MAX_LIMIT, format, args) < CHAR_MAX_LIMIT);

    printf(buffer);
    vfprintf(fileHandle, format, args);
    va_end(args);
}

void openLogStream()
{
    openFile(FILE_NAME, TYPE_TEXT, MODE_WRITE, &fileHandle);
    fprintf(fileHandle, "===========Logging Begin===========\n");
}

void closeLogStream()
{
    fprintf(fileHandle, "===========Logging End=============\n");
    closeFile(fileHandle);
}
