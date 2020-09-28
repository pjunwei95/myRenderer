#pragma once
#include "array.h"
#include <stdint.h>

struct CircularBuffer
{
    Array m_Array;
    int m_Front;
    int m_Back;
};

int getCapacityCircBuff(const CircularBuffer * const cb);

int getSizeCircBuf(const CircularBuffer * const cb);

bool isFullCircBuf(const CircularBuffer * const cb);

void pushBackCircBuf(CircularBuffer * const cb, const void * srcData);

void * popFrontCircBuf(CircularBuffer * const cb);

void freeCircBuf(CircularBuffer * const cb);

void testCircularBuffer();

CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);

int getFrontIdxCircBuf(const CircularBuffer * const cb);

void * getFrontCircBuf(const CircularBuffer * const cb);
