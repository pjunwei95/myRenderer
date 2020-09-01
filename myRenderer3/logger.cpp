#include "fileManager.h"
#include "logger.h"

#define FILE_NAME "debug.txt"

void log(const char * msg)
{
    FileHandle fileHandle;

    openFile(FILE_NAME, "a", &fileHandle);
    //write output to file
    fprintf(fileHandle, "===========Logging Begin===========\n");
    fprintf(fileHandle, msg);
    fprintf(fileHandle, "===========Logging End===========\n");
    closeFile(fileHandle);
}
