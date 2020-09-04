#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>
#include "bufferOps.h"
//#define NDEBUG
#include <cassert>

bool openFile(const char* fileName, OpenType openType, FileMode fileMode, FileHandle * fileHandle)
{
    errno_t err = NULL;
    if (fileMode == MODE_WRITE)
        err = fopen_s(fileHandle, fileName, "w");
    else if (fileMode == MODE_APPEND)
        err = fopen_s(fileHandle, fileName, "a");
    else if (fileMode == MODE_READ && openType == TYPE_TEXT)
        err = fopen_s(fileHandle, fileName, "r"); 
    else if (fileMode == MODE_READ && openType == TYPE_BIN)
        err = fopen_s(fileHandle, fileName, "rb");

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        return false;
    }
    else
    {
        //printf("-------------Opening File \"%s\"\n", fileName);
        return true;
    }
}

bool closeFile(FileHandle fileHandle) 
{
    assert(fileHandle);
    if (!fileHandle) 
    {
        return false;
    }
    else
    {
        //printf("-------------Closing File\n");
        fclose(fileHandle);
    }
    return true;
}

void freeBuffer(char* buffer)
{
    free(buffer);
}

void readToBuffer(const FileHandle fileHandle, char * buffer, long length)
{
    if (buffer)
    {
        size_t value = fread(buffer, 1, length, fileHandle);
        assert(value == length);
        buffer[value] = '\0';
    }
    else
        printf("Error reading to buffer!\n");
}

void readAndProcessFile(const char * fileName, OpenType openType)
{
    FileHandle fileHandle;

    openFile(fileName, openType, MODE_READ, &fileHandle);

    char * buffer = 0;
    long length;

    fseek(fileHandle, 0, SEEK_END);
    length = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);

    readToBuffer(fileHandle, buffer, length);

    closeFile(fileHandle);

    //if (openType == TYPE_TEXT)
        //tokeniseBuffer(buffer);

    freeBuffer(buffer);
}
