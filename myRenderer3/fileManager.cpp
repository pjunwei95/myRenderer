#include "fileManager.h"
#include "bufferOps.h"

void FileManager::OpenFile(const char* fileName, OpenType openType, FileMode fileMode)
{
    assert(fileName);
    errno_t err = NULL;
    const char* mode;
    if (fileMode == MODE_WRITE)
        mode = "w";
    else if (fileMode == MODE_APPEND)
        mode = "a";
    else if (fileMode == MODE_READ && openType == TYPE_TEXT)
        mode = "r";
    else if (fileMode == MODE_READ && openType == TYPE_BIN)
        mode = "rb";
    else
        mode = nullptr;

    err = fopen_s(&m_FileHandle, fileName, mode);
    SetFileSize();

    if (err)
        logmsg("Error opening data file %s\n", fileName);
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

// always return length + 1 to account for null terminating character
void FileManager::SetFileSize()
{
    assert(m_FileHandle);
    fseek(m_FileHandle, 0, SEEK_END);
    m_FileSize = ftell(m_FileHandle) + 1;
    fseek(m_FileHandle, 0, SEEK_SET);
    assert(m_FileSize);
}

//char* FileManager::ReadBuffer()
//{
//    char* buffer = 0;
//    fseek(m_FileHandle, 0, SEEK_END);
//    long length = ftell(m_FileHandle);
//    fseek(m_FileHandle, 0, SEEK_SET);
//    buffer = (char*)malloc(length + 1);
//    assert(buffer);
//    assert(length);
//    size_t value = fread(buffer, 1, length, m_FileHandle);
//    assert(value < length);
//    buffer[value] = '\0';
//    return buffer;
//}

//char* FileManager::ReadBufferWithLength(char* buffer, long length)
//{
//    assert(buffer);
//    size_t value = fread(buffer, 1, length, m_FileHandle);
//    assert(value < length);
//    buffer[value] = '\0';
//    return buffer;
//}

