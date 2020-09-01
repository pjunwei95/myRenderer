#pragma once
#include <stdio.h>

typedef FILE * FileHandle;

typedef const char * OpenType;

void manageFile();

bool openFile(const char * fileName, OpenType openType, FileHandle * fileHandle);

bool closeFile(FileHandle fileHandle);

char * readFileToBuffer(FileHandle fileHandle);
