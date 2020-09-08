#pragma once
#include <stdio.h>

typedef FILE * FileHandle;

enum OpenType
{
    TYPE_TEXT,
    TYPE_BIN
};

enum FileMode
{
    MODE_READ,
    MODE_WRITE,
    MODE_APPEND
};

bool openFile(const char * fileName, OpenType openType, FileMode fileMode, FileHandle * fileHandle);

bool closeFile(FileHandle fileHandle);

void readAndProcessFile(const char * fileName, OpenType openType);
