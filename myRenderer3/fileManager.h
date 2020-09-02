#pragma once
#include <stdio.h>

typedef FILE * FileHandle;

typedef const char * OpenType;

void readFile(const char * fileName, OpenType openType);

bool openFile(const char * fileName, OpenType openType, FileHandle * fileHandle);

bool closeFile(FileHandle fileHandle);

char * readFileToBuffer(FileHandle fileHandle);

void processBuffer(char * buffer);

void freeBuffer(char * buffer);
