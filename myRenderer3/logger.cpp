#include "fileManager.h"
#include "logger.h"

#include <vector>
#include <cstdio>
#include <cstdarg>

#define FILE_NAME "debug.txt"

FileHandle fileHandle;

void logmsg(const char *format, ...)
{
    va_list args1;
    va_start(args1, format);
    va_list args2;
    va_copy(args2, args1);
    std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, format, args1));
    va_end(args1);
    std::vsnprintf(buf.data(), buf.size(), format, args2);
    va_end(args2);
    printf("%s", buf.data());
    fprintf(fileHandle, buf.data());
}

void openLogStream()
{
    openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    fprintf(fileHandle, "===========Logging Begin===========\n");
    //closeFile(fileHandle);
}

void closeLogStream()
{

    //openFile(FILE_NAME, TYPE_TEXT, MODE_APPEND, &fileHandle);
    fprintf(fileHandle, "===========Logging End=============\n");
    closeFile(fileHandle);
}



