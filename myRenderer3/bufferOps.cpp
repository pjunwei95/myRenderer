#include <Windows.h>
#include "logger.h"
#include "bufferOps.h"

//#define NDEBUG
#include <cassert>

void tokeniseBuffer(char * buffer)
{
    assert(buffer != NULL);
    //logmsg("buffer:\n%s\n", buffer);
    char *nextToken;
    const char * delim = " \r\n";
    char * token = strtok_s(buffer, delim, &nextToken);
    while (token != NULL)
    {
        //logmsg("token = %s\n", token);
        token = strtok_s(NULL, delim, &nextToken);
    }
}
