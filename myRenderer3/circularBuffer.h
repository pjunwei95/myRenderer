#pragma once
#include "array.h"

struct CircularBuffer
{
    Array m_Array;
    int m_Front;
    int m_Back;
};

void testCircularBuffer();
