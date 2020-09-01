#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>

// config.txt
/*
    debug
    arg2
    arg3
*/


void readFile(const char * fileName)
{
    FileHandle fileHandle;

    openFile(fileName, "rb", &fileHandle);

    char* buffer = readFileToBuffer(fileHandle);

    closeFile(fileHandle);

    freeBuffer(buffer);
}

bool openFile(const char* fileName, OpenType openType, FileHandle * fileHandle)
{
    errno_t err = fopen_s(fileHandle, fileName, openType);

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        return 0;
    }
    else
    {
        printf("-------------Opening File \"%s\"\n", fileName);
        return 1;
    }
}

bool closeFile(FileHandle fileHandle) 
{
    if (!fileHandle) 
    {
        return 0;
    }
    else
    {
        printf("-------------Closing File\n");
        fclose(fileHandle);
    }
    return 1;
}

//TODO handle binary
char* readFileToBuffer(FileHandle fileHandle)
{
    char * buffer = 0;
    long length;
    fseek(fileHandle, 0, SEEK_END);
    length = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);
    if (buffer)
    {
        fread(buffer, 1, length, fileHandle);
    }
    buffer[length] = '\0';
    return buffer;
 }

void freeBuffer(char* buffer)
{
    free(buffer);
}

