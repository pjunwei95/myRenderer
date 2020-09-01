#include "timer.h"

Timer nFrequency;

void initialiseTimer()
{
    QueryPerformanceFrequency(&nFrequency); //to be called only once. not per frame
}
