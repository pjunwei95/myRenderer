#pragma once
#include <stdio.h>

typedef FILE * FileHandle;

typedef const char * OpenType;

void loadConfig();

bool openFile(const char * fileName, OpenType openType, FileHandle * fileHandle);

bool closeFile(FileHandle fileHandle);

void freeBuffer(char * buffer);
