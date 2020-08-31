#include "Timer.h"

Timer nFrequency;

void InitialiseTimer()
{
    QueryPerformanceFrequency(&nFrequency); //to be called only once. not per frame
}
