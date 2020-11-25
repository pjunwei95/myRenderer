#pragma once
#include <stdio.h>

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

    ~FileManager()
    {
    }

    inline FileHandle GetFileHandle() { return m_FileHandle; }
    bool OpenFile(const char * fileName, OpenType openType, FileMode fileMode);
    void CloseFile();
    void readAndProcessFile(const char * fileName, OpenType openType);
private:
    FileHandle m_FileHandle;
};
