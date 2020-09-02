#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>
#include "isValidArgs.h"

void tokeniseBuffer(char * buffer);

char* readFile(const char * fileName, OpenType openType)
{
    FileHandle fileHandle;

    openFile(fileName, openType, &fileHandle);

    char* buffer = readFileToBuffer(fileHandle);

    if (!buffer)
        printf("Error writing to buffer!\n");

    closeFile(fileHandle);
    return buffer;
}

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

char* readFileToBuffer(FileHandle fileHandle)
{
    char * buffer = 0;
    long length;
    fseek(fileHandle, 0, SEEK_END);
    length = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);
    if (buffer)
    {
        fread(buffer, 1, length, fileHandle);
        buffer[length] = '\0';

    }
    return buffer;
 }

void freeBuffer(char* buffer)
{
    free(buffer);
}

void loadConfig()
{
    printf("Loading default configurations\n");

    char* buffer;

    buffer = readFile("config.txt", "rb"); //issues with using "r"

    tokeniseBuffer(buffer);

    freeBuffer(buffer);
}

void tokeniseBuffer(char * buffer)
{
    char *nextToken;
    char * token = strtok_s(buffer, " ", &nextToken);
    while (token != NULL)
    {
        printf("token = %s\n", token);
        token = strtok_s(NULL, " ", &nextToken);
    }
}