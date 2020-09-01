#include "fileManager.h"
#include <Windows.h>
#include <stdio.h>


#define TEMP_MAX_CHAR 256
#define NUM_STRINGS 50
#define LOGNAME "debug.log"


//bool OpenFile(const char* FileName, OpenType openType, FileHandle fileHandle)

void manageFile()
{
    FileHandle fileHandle;
    openFile("config.txt", "rb", fileHandle);

    closeFile(fileHandle);
}

bool openFile(const char* fileName, OpenType openType, FileHandle fileHandle)
{
    char * buffer = 0;
    long length;
    errno_t err = fopen_s(&fileHandle, fileName, openType);

    if (err)
    {
        printf("Error opening data file %s\n", fileName);
        return 0;
    }
    else
    {
        printf("-------------Reading File \"%s\"-------------\n", fileName);
        return 1;
    }
}


bool closeFile(FileHandle fileHandle) 
{
    printf("-------------Closing File-------------\n");
    fclose(fileHandle);
}

//void function() 
//{
    //char strArr[NUM_STRINGS][TEMP_MAX_CHAR];
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
//    // config.txt
//    /*
//        debug
//        arg2
//        arg3
//    */
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
