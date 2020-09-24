#include "circularBuffer.h"
#include <iostream>
#include "assert.h"

#define BUFFER_LENGTH 3

void printCircBuf(const CircularBuffer* const cb);

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
CircularBuffer createNewCircBuf(const void* const elemVal, unsigned int sizeElem)
{
    CircularBuffer cb;
    cb.m_Array = createNewFilledArray(BUFFER_LENGTH, elemVal, sizeElem);
    cb.m_Front = 0;
    cb.m_Back = 0;
    return cb;
}

void popCircBuf(CircularBuffer* const cb)
{
    assert(cb->m_Array.m_Data);
    if (cb->m_Front == cb->m_Back)
    {
        cb->m_Front = (cb->m_Front + 1) % BUFFER_LENGTH;
    }
}

//Assuming fixed size buffer
void pushCircBuf(CircularBuffer* const cb, const void* srcData)
{
    assert(cb->m_Array.m_Data);
    assert(srcData);
    assert(cb->m_Array.m_Size <= cb->m_Array.m_Capacity);//check for indices instead

    //'push' a value directly into the 'back' slot
    void* dstIdx = getArrayAt(&cb->m_Array, cb->m_Back);
    //array[back] = srcData;
    memcpy(dstIdx, srcData, cb->m_Array.m_TypeSize);

    // When you 'pop', you simply move the 'front' cursor forward by one
    // Advances front to be always in front of back
    popCircBuf(cb);

    // Advances back
    cb->m_Back = (cb->m_Back + 1) % BUFFER_LENGTH;
}

void freeCircBuf(CircularBuffer* const cb)
{
    assert(cb);
    freeArray(&cb->m_Array);
}

void testCircularBuffer()
{
    int empty = 0;
    CircularBuffer intCircBuf = createNewCircBuf(&empty, sizeof(int));

    //push 10 numbers
    for (int i = 0; i < 15; ++i)
    {
        pushCircBuf(&intCircBuf, &i);
    }

    //print to console
    printCircBuf(&intCircBuf);

    printf("Popping and pushing 99...\n");
    popCircBuf(&intCircBuf);
    int rand = 99;
    pushCircBuf(&intCircBuf, &rand);

    printCircBuf(&intCircBuf);

    freeCircBuf(&intCircBuf);
}

void printCircBuf(const CircularBuffer* const cb)
{
    int tempFront = cb->m_Front;
    printf("Reading..\n");
    for (int i = 0; i < BUFFER_LENGTH; ++i)
    {
        int idx = (tempFront + i) % BUFFER_LENGTH;
        void* ptr = (unsigned char*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        printf("%d ", *((int*)ptr));
    }
    printf("\n");
}