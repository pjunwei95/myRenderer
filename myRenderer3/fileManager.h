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
    bool OpenFile(const char * fileName, OpenType openType, FileMode fileMode);
    void CloseFile();
    void readAndProcessFile(const char * fileName, OpenType openType);
    char* ReadBuffer();
    char* ReadBufferWithLength(char* buffer, long length)
    {
        assert(buffer);
        size_t value = fread(buffer, 1, length, m_FileHandle);
        assert(value < length);
        buffer[value] = '\0';
        return buffer;
    }

    // always return length + 1 to account for null terminating character
    long GetBufferLength()
    {
        assert(m_FileHandle);
        fseek(m_FileHandle, 0, SEEK_END);
        long length = ftell(m_FileHandle);
        fseek(m_FileHandle, 0, SEEK_SET);
        assert(length);
        return length + 1;
    }
private:
    FileHandle m_FileHandle;
};
