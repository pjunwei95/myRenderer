#pragma once
#include "array.h"
#include <stdint.h>

struct CircularBuffer
{
    Array m_Array;
    int m_Front;
    int m_Back;
};

void pushBackCircBuf(CircularBuffer * const cb, const void * srcData);

void * popFrontCircBuf(CircularBuffer * const cb);

void freeCircBuf(CircularBuffer * const cb);

void testCircularBuffer();

CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);
