#include <Windows.h>
#include "logger.h"
#include "bufferOps.h"

void tokeniseBuffer(char * buffer)
{
    //printf("buffer:\n%s\n", buffer);
    char *nextToken;
    const char * delim = " \r\n";
    char * token = strtok_s(buffer, delim, &nextToken);
    while (token != NULL)
    {
        logmsg("token = %s\n", token);
        token = strtok_s(NULL, delim, &nextToken);
    }
}
