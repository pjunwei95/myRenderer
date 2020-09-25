#pragma once
#include "array.h"
#include <stdint.h>

struct CircularBuffer
{
    Array m_Array;
    int m_Front;
    int m_Back;
};

void testCircularBuffer();
