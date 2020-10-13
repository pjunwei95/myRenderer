#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>
#include "bufferOps.h"
//#define NDEBUG
#include <assert.h>

bool FileManager::openFile(const char* fileName, OpenType openType, FileMode fileMode, FileHandle* fileHandle)
{
    assert(fileName);
    assert(fileHandle);

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
    return true;
}

void FileManager::closeFile(FileHandle fileHandle)
{
    assert(fileHandle);
    fclose(fileHandle);
}

void readToBuffer(const FileManager::FileHandle fileHandle, char* buffer, long length)
{
    assert(fileHandle);
    assert(buffer);
    assert(length);
    size_t value = fread(buffer, 1, length, fileHandle);
    assert(value < length);
    buffer[value] = '\0';
}

void FileManager::readAndProcessFile(const char* fileName, OpenType openType)
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

    if (openType == TYPE_TEXT)
        tokeniseBuffer(buffer);

    free(buffer);
}
