#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>

void tokeniseBuffer(char * buffer);


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

void writeToBuffer(const FileHandle fileHandle, char * buffer, long length)
{
    if (buffer)
    {
        fread(buffer, 1, length, fileHandle);
        buffer[length] = '\0';
    }
    else
        printf("Error writing to buffer!\n");
}

void readAndProcessFile(const char * fileName, OpenType openType)
{
    FileHandle fileHandle;

    openFile(fileName, openType, &fileHandle);

    char * buffer = 0;
    long length;

    fseek(fileHandle, 0, SEEK_END);
    length = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);

    writeToBuffer(fileHandle, buffer, length);

    closeFile(fileHandle);

    tokeniseBuffer(buffer);

    freeBuffer(buffer);
}
void loadConfig()
{
    //you can always assume the "config.txt" file will always be present. if not, init default values

    printf("Loading default configurations\n");

    readAndProcessFile("config.txt", "rb"); //issues with using "r"
}




