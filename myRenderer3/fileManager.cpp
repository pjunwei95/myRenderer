#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>
#include "bufferOps.h"
//#define NDEBUG

bool FileManager::OpenFile(const char* fileName, OpenType openType, FileMode fileMode)
{
    assert(fileName);

    errno_t err = NULL;
    if (fileMode == MODE_WRITE)
        err = fopen_s(&m_FileHandle, fileName, "w");
    else if (fileMode == MODE_APPEND)
        err = fopen_s(&m_FileHandle, fileName, "a");
    else if (fileMode == MODE_READ && openType == TYPE_TEXT)
        err = fopen_s(&m_FileHandle, fileName, "r");
    else if (fileMode == MODE_READ && openType == TYPE_BIN)
        err = fopen_s(&m_FileHandle, fileName, "rb");

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        return false;
    }
    return true;
}

void FileManager::CloseFile()
{
    assert(m_FileHandle);
    fclose(m_FileHandle);
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
    OpenFile(fileName, openType, MODE_READ);

    char * buffer = 0;

    fseek(m_FileHandle, 0, SEEK_END);
    long length = ftell(m_FileHandle);
    fseek(m_FileHandle, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);

    readToBuffer(m_FileHandle, buffer, length);

    CloseFile();

    if (openType == TYPE_TEXT)
        tokeniseBuffer(buffer);

    free(buffer);
}

char* FileManager::ReadBuffer()
{
    char* buffer = 0;
    fseek(m_FileHandle, 0, SEEK_END);
    long length = ftell(m_FileHandle);
    fseek(m_FileHandle, 0, SEEK_SET);
    buffer = (char*)malloc(length + 1);
    assert(buffer);
    assert(length);
    size_t value = fread(buffer, 1, length, m_FileHandle);
    assert(value < length);
    buffer[value] = '\0';
    return buffer;
}