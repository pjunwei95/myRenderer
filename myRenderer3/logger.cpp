#include "fileManager.h"
#include "logger.h"
#include <stdarg.h>
#include <cassert>
#include <string.h>
#include <Windows.h>

#define CHAR_MAX_LIMIT 256

FileManager logManager;

void logmsg(const char *format, ...)
{
    assert(format); //check if null

    char buffer[CHAR_MAX_LIMIT];
    va_list args;
    va_start(args, format);
    int err = vsnprintf_s(buffer, CHAR_MAX_LIMIT, format, args);
    assert(err > 0);    
    assert(err < CHAR_MAX_LIMIT);

    OutputDebugString(buffer); //to output
    //printf(buffer); //to console
    va_end(args);
}

void logfile(const char *format, ...)
{
    assert(format); //check if null

    char buffer[CHAR_MAX_LIMIT];
    va_list args;
    va_start(args, format);
    int err = vsnprintf_s(buffer, CHAR_MAX_LIMIT, format, args);
    assert(err > 0);
    assert(err < CHAR_MAX_LIMIT);

    OutputDebugString(buffer); //to output
    vfprintf(logManager.GetFileHandle(), format, args); //to file
    va_end(args);
}


void openLogStream(const char* fileName)
{
    logManager.OpenFile(fileName, FileManager::TYPE_TEXT, FileManager::MODE_WRITE);
    OutputDebugString("===========Output Begin===========\n");
    fprintf(logManager.GetFileHandle(), "===========Logging Begin===========\n");
}

void closeLogStream()
{
    OutputDebugString("===========Output End=============\n");
    fprintf(logManager.GetFileHandle(), "===========Logging End=============\n");
    logManager.CloseFile();
}
