#include <windows.h>
#include "bool.h"

void setBool(BOOL boolean, BOOL value)
{
    boolean = value;
}

BOOL getBool(BOOL boolean)
{
    return boolean;
}