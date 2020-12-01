#pragma once
#include "array.h"

class FileManager
{
public:
    typedef FILE* FileHandle;

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

    FileManager()
        : m_FileHandle{ nullptr }
    {
    }

    FileManager(const char* fileName, OpenType openType, FileMode fileMode)
        : m_FileHandle{ nullptr }
    {
        OpenFile(fileName, openType, fileMode);
    }

    ~FileManager()
    {
        if (m_FileHandle)
            CloseFile();
    }

    inline FileHandle GetFileHandle() { return m_FileHandle; }
    inline uint32_t GetFileSize() { return m_FileSize; }

    void OpenFile(const char * fileName, OpenType openType, FileMode fileMode);
    void CloseFile();
    void readAndProcessFile(const char * fileName, OpenType openType);
    void SetFileSize(); // always return length + 1 to account for null terminating character
    //char* ReadBuffer();
    //char* ReadBufferWithLength(char* buffer, long length);
    
    template<typename T>
    void ReadArray(Array<T>& buffer);

private:
    FileHandle m_FileHandle;
    uint32_t m_FileSize;
};

template<typename T>
void FileManager::ReadArray(Array<T>& array)
{
    assert(!array.size());
    int c;
    while ((c = fgetc(m_FileHandle)) != EOF)
    {
        array.pushBack((T)c);
    }
    array.pushBack(0);
    assert(array.size() < (uint32_t)m_FileSize);
}