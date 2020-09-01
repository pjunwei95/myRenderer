#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>


#define TEMP_MAX_CHAR 256
#define NUM_STRINGS 50
#define LOGNAME "debug.log"

// config.txt
/*
    debug
    arg2
    arg3
*/

void manageFile()
{
    FileHandle fileHandle;

    openFile("config.txt", "rb", &fileHandle);

    char* buffer = readFileToBuffer(fileHandle);
    buffer;

    closeFile(fileHandle);
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
        printf("-------------Opening File \"%s\"-------------\n", fileName);
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
        printf("-------------Closing File-------------\n");
        fclose(fileHandle);
    }
    return 1;
}


//TODO handle binary
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
    }
    buffer[length] = '\0';
    return buffer;
 }




// char* readFileToBuffer(FileHandle fileHandle)
// void freeBuffer(const char*)

//void function(FileHandle fileHandle) 
//{
//    char * buffer = 0;
//    long length;
//    char strArr[NUM_STRINGS][TEMP_MAX_CHAR];
//
//    fseek(fileHandle, 0, SEEK_END);
//    length = ftell(fileHandle);
//    fseek(fileHandle, 0, SEEK_SET);
//    buffer = (char *)malloc(length + 1);
//    if (buffer)
//    {
//        fread(buffer, 1, length, fileHandle);
//    }
//    
//    buffer[length] = '\0';
//
//    if (buffer) //TODO openType == r
//    {
//        //do nothing
//    }
//    free(buffer);
//
//    
//}

//FILE* startLog()
//{
//    const char* fileName = LOGNAME;
//    /* open output file */
//
//    //check whether is overwriting
//    errno_t err = fopen_s(&pfout, fileName, "a");
//
//    if (err)
//    {
//        printf("Error opening data file %s\n", fileName);
//        printf("Cannot write to log\n");
//        //dont shutdown at every logging
//    }
//    else
//    {
//        fprintf(pfout, "===========Logging Begin===========\n");
//    }
//
//    return pfout;
//}
//
//void endLog(FILE* pf)
//{
//    fprintf(pf, "===========Logging End===========\n");
//
//    fclose(pf);
//}
