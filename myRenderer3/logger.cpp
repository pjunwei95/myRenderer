#include "fileManager.h"
#include "logger.h"
#include <stdarg.h>
#include <cassert>
#include <string.h>
#include <Windows.h>

#define FILE_NAME "debug.txt"
#define CHAR_MAX_LIMIT 256

FileManager::FileHandle fileHandle;

void logmsg(const char *format, ...)
{
    assert(format); //check if null

    char buffer[CHAR_MAX_LIMIT];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, CHAR_MAX_LIMIT, format, args);

    assert(vsnprintf(buffer, CHAR_MAX_LIMIT, format, args) < CHAR_MAX_LIMIT);

    OutputDebugString(buffer); //to output
    printf(buffer); //to console
    vfprintf(fileHandle, format, args); //to file
    va_end(args);
}

void openLogStream()
{
    FileManager fm;
    fm.openFile(FILE_NAME, FileManager::TYPE_TEXT, FileManager::MODE_WRITE, &fileHandle);
    OutputDebugString("===========Logging Begin===========\n");
    printf("===========Logging Begin===========\n");
    fprintf(fileHandle, "===========Logging Begin===========\n");
}

void closeLogStream()
{
    FileManager fm;
    OutputDebugString("===========Logging End=============\n");
    printf("===========Logging End=============\n");
    fprintf(fileHandle, "===========Logging End=============\n");
    fm.closeFile(fileHandle);
}
