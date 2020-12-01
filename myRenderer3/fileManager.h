#pragma once
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
    void OpenFile(const char * fileName, OpenType openType, FileMode fileMode);
    void CloseFile();
    void readAndProcessFile(const char * fileName, OpenType openType);

    char* ReadBuffer();
    char* ReadBufferWithLength(char* buffer, long length);
    //void ReadCharArrayWithLength(Array<char> buffer, long length);
    long GetBufferLength(); // always return length + 1 to account for null terminating character
private:
    FileHandle m_FileHandle;
};
