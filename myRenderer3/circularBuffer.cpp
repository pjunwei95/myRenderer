#include "circularBuffer.h"
#include <iostream>
#include "assert.h"
#include <stdlib.h>
#include "logger.h"

void printCircBuf(const CircularBuffer* const cb);

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
CircularBuffer createNewCircBuf(unsigned int bufferLength, const void* const elemVal, unsigned int sizeElem)
{
    CircularBuffer cb;
    cb.m_Array = createNewFilledArray(bufferLength, elemVal, sizeElem);
    cb.m_IsFull = false;
    cb.m_Front = 0;
    cb.m_Back = 0;
    return cb;
}

void* getCircBufFront(const CircularBuffer* const cb)
{
    return getArrayAt(&cb->m_Array, cb->m_Front);
}

void* getCircBufBack(const CircularBuffer* const cb)
{
    return getArrayAt(&cb->m_Array, cb->m_Back);
}

int getCircBufSize(const CircularBuffer* const cb)
{
    return abs(cb->m_Front - cb->m_Back); //difference in m_Front & m_Back
}

bool isCircBufFull(const CircularBuffer* const cb)
{
    return cb->m_IsFull;
}

bool isCircBufEmpty(const CircularBuffer* const cb)
{
    return cb->m_Front == cb->m_Back && !isCircBufFull(cb);
}

//'push' a value directly into the 'back' slot
void pushBackCircBuf(CircularBuffer* const cb, const void* srcData)
{
    assert(cb);
    assert(srcData);
    assert(!isCircBufFull(cb));

    // buffer[back]
    void* addressAtBack = getArrayAt(&cb->m_Array, cb->m_Back);
    memcpy(addressAtBack, srcData, getArrayTypeSize(&cb->m_Array));

    cb->m_Back = (cb->m_Back + 1) % getArraySize(&cb->m_Array);

    if (cb->m_Front == cb->m_Back)
        cb->m_IsFull = true;
}

void pushFrontCircBuf(CircularBuffer* const cb, const void* srcData)
{
    assert(cb);
    assert(srcData);
    assert(!isCircBufFull(cb));

    // buffer[front]
    void* addressAtFront = getArrayAt(&cb->m_Array, cb->m_Front);
    memcpy(addressAtFront, srcData, getArrayTypeSize(&cb->m_Array));

    cb->m_Front = (cb->m_Front + 1) % getArraySize(&cb->m_Array);

    if (cb->m_Front == cb->m_Back)
        cb->m_IsFull = true;
}

// When you 'pop', you simply move the 'front' cursor forward by one
void* popFrontCircBuf(CircularBuffer* const cb)
{
    assert(!isCircBufEmpty(cb));
    void* addressAtFront = getArrayAt(&cb->m_Array, cb->m_Front);
    cb->m_Front = (cb->m_Front + 1) % getArraySize(&cb->m_Array);

    cb->m_IsFull = false;
    return addressAtFront;
}

void* popBackCircBuf(CircularBuffer* const cb)
{
    assert(!isCircBufEmpty(cb));
    void* addressAtBack = getArrayAt(&cb->m_Array, cb->m_Back);
    cb->m_Back = (cb->m_Back + 1) % getArraySize(&cb->m_Array);

    cb->m_IsFull = false;
    return addressAtBack;
}

void clearCircBuf(CircularBuffer* cb)
{
    assert(!isCircBufEmpty(cb));
    cb->m_Front = 0;
    cb->m_Back = 0;
    cb->m_IsFull = false;
}

void freeCircBuf(CircularBuffer* const cb)
{
    assert(cb);
    freeArray(&cb->m_Array);
}

void testCircularBuffer()
{
    int empty = 0;
    CircularBuffer intCircBuf = createNewCircBuf(5, &empty, sizeof(int));

    for (int i = 1; i <= 5; ++i)
    {
        //pushCircBuf(&intCircBuf, &i);
        pushBackCircBuf(&intCircBuf, &i);
    }

    //print to console
    printCircBuf(&intCircBuf);

    logmsg("Popping...\n");
    popFrontCircBuf(&intCircBuf);
    printCircBuf(&intCircBuf);

    logmsg("Popping...\n");
    popFrontCircBuf(&intCircBuf);
    printCircBuf(&intCircBuf);

    logmsg("Pushing 99...\n");
    int rand = 99;
    pushBackCircBuf(&intCircBuf, &rand);
    printCircBuf(&intCircBuf);

    freeCircBuf(&intCircBuf);
}

void printCircBuf(const CircularBuffer* const cb)
{
    int tempFront = cb->m_Front;
    logmsg("=========\n");
    for (int i = 0; i < getArraySize(&cb->m_Array); ++i)
    {
        int idx = (tempFront + i) % getArraySize(&cb->m_Array);
        if (idx == cb->m_Back && !isCircBufFull(cb))
            break;
        void* ptr = (unsigned char*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        logmsg("%d ", *((int*)ptr));
    }
    logmsg("\n==========\n");
}