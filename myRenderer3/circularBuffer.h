#pragma once
#include "array.h"

struct CircularBuffer
{
    Array array;
    int front, back;
};

void testCircularBuffer();
