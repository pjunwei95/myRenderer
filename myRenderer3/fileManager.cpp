#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>

void tokeniseBuffer(char * buffer);


bool openFile(const char* fileName, OpenType openType, FileMode fileMode, FileHandle * fileHandle)
{
    errno_t err = NULL;
    if (fileMode == MODE_WRITE)
        err = fopen_s(fileHandle, fileName, "w");
    else if (fileMode == MODE_APPEND)
        err = fopen_s(fileHandle, fileName, "a");
    else if (fileMode == MODE_READ && openType == TYPE_TEXT)
        err = fopen_s(fileHandle, fileName, "r"); //issues with using "r" printing extra
    else if (fileMode == MODE_READ && openType == TYPE_BIN)
        err = fopen_s(fileHandle, fileName, "rb");

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        return false;
    }
    else
    {
        printf("-------------Opening File \"%s\"\n", fileName);
        return true;
    }
}

bool closeFile(FileHandle fileHandle) 
{
    if (!fileHandle) 
    {
        return false;
    }
    else
    {
        printf("-------------Closing File\n");
        fclose(fileHandle);
    }
    return true;
}

void tokeniseBuffer(char * buffer)
{
    //printf("buffer:\n%s\n", buffer);
    char *nextToken;
    const char * delim = " \n";
    char * token = strtok_s(buffer, delim, &nextToken);
    while (token != NULL)
    {
        printf("token = %s\n", token);
        token = strtok_s(NULL, delim, &nextToken);
    }
}

void freeBuffer(char* buffer)
{
    free(buffer);
}

void readToBuffer(const FileHandle fileHandle, char * buffer, long length)
{
    if (buffer)
    {
        fread(buffer, 1, length, fileHandle);
        buffer[length] = '\0';
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

    if (openType == TYPE_TEXT)
        tokeniseBuffer(buffer);

    freeBuffer(buffer);
}

void loadConfig()
{
    //you can always assume the "config.txt" file will always be present. if not, init default values

    printf("Loading default configurations\n");

    readAndProcessFile("config.txt", TYPE_TEXT); 
}
