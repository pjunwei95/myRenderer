#include "circularBuffer.h"
#include <iostream>
#include "assert.h"
#include <stdlib.h>
#include "logger.h"

void printCircBuf(const CircularBuffer* const cb);

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem)
{
    CircularBuffer cb;
    cb.m_Array = createNewFilledArray(bufferLength, sizeElem);
    cb.m_Front = 0;
    cb.m_Back = 0;
    return cb;
}

void* getFrontCircBuf(const CircularBuffer* const cb)
{
    return getArrayAt(&cb->m_Array, cb->m_Front);
}

void* getBackCircBuf(const CircularBuffer* const cb)
{
    return getArrayAt(&cb->m_Array, cb->m_Back);
}

int getSizeCircBuf(const CircularBuffer* const cb)
{
    //difference in m_Front & m_Back
    if (cb->m_Front == cb->m_Back)
    {
        //TODO handle empty or full
        if (isArrayEmpty(&cb->m_Array))
            return 0;
        else
            return getArrayCapacity(&cb->m_Array);
    }
    else
        return abs(cb->m_Front - cb->m_Back);
}

bool isFullCircBuf(const CircularBuffer* const cb)
{
    return getSizeCircBuf(cb) == getArrayCapacity(&cb->m_Array);
}

bool isCircBufEmpty(const CircularBuffer* const cb)
{
    return cb->m_Front == cb->m_Back && !isFullCircBuf(cb);
}

//'push' a value directly into the 'back' slot
void pushBackCircBuf(CircularBuffer* const cb, const void* srcData)
{
    assert(cb);
    assert(srcData);
    assert(!isFullCircBuf(cb));
    cb->m_Array.m_Size++;

    // buffer[back]
    void* addressAtBack = getArrayAt(&cb->m_Array, cb->m_Back);
    memcpy(addressAtBack, srcData, getArrayTypeSize(&cb->m_Array));

    cb->m_Back = (cb->m_Back + 1) % getArrayCapacity(&cb->m_Array);
}


// When you 'pop', you simply move the 'front' cursor forward by one
void* popFrontCircBuf(CircularBuffer* const cb)
{
    assert(!isCircBufEmpty(cb));
    void* addressAtFront = getArrayAt(&cb->m_Array, cb->m_Front);
    cb->m_Front = (cb->m_Front + 1) % getArrayCapacity(&cb->m_Array);

    return addressAtFront;
}

void clearCircBuf(CircularBuffer* cb)
{
    assert(!isCircBufEmpty(cb));
    cb->m_Front = 0;
    cb->m_Back = 0;
}

void freeCircBuf(CircularBuffer* const cb)
{
    assert(cb);
    freeArray(&cb->m_Array);
}

void testCircularBuffer()
{
    //int empty = 0;
    CircularBuffer intCircBuf = createNewCircBuf(3, sizeof(int));

    for (int i = 0; i < 3; ++i)
    {
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
    for (int i = 0; i < getArrayCapacity(&cb->m_Array); ++i)
    {
        int idx = (tempFront + i) % getArrayCapacity(&cb->m_Array);
        if (idx == cb->m_Back && !isFullCircBuf(cb))
            break;
        void* ptr = (unsigned char*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        logmsg("%d ", *((int*)ptr));
    }
    logmsg("\n==========\n");
}