#include "circularBuffer.h"
#include <iostream>
#include "assert.h"

#define BUFFER_LENGTH 3

void printCircBuf(const CircularBuffer* const cb);

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
CircularBuffer cb_create_new(const void* const elemVal, unsigned int sizeElem)
{
    CircularBuffer cb;
    cb.m_Array = a_create_new_filled(BUFFER_LENGTH, elemVal, sizeElem);
    cb.m_Front = 0;
    cb.m_Back = 0;
    return cb;
}

void cb_pop(CircularBuffer* const cb)
{
    assert(cb->m_Array.m_Data);
    if (cb->m_Front == cb->m_Back)
    {
        cb->m_Front = (cb->m_Front + 1) % BUFFER_LENGTH;
    }
}

//Assuming fixed size buffer
void cb_push(CircularBuffer* const cb, const void* srcData)
{
    assert(cb->m_Array.m_Data);
    assert(srcData);
    assert(cb->m_Array.m_Size < cb->m_Array.m_Capacity);//check for indices instead

    //'push' a value directly into the 'back' slot
    void* dstIdx = a_at(&cb->m_Array, cb->m_Back);
    //array[back] = srcData;
    memcpy(dstIdx, srcData, cb->m_Array.m_TypeSize);

    // When you 'pop', you simply move the 'front' cursor forward by one
    // Advances front to be always in front of back
    cb_pop(cb);

    // Advances back
    cb->m_Back = (cb->m_Back + 1) % BUFFER_LENGTH;
}

void cb_free(CircularBuffer* const cb)
{
    assert(cb);
    a_free(&cb->m_Array);
}

void testCircularBuffer()
{
    int empty = 0;
    CircularBuffer intCircBuf = cb_create_new(&empty, sizeof(int));

    //push 10 numbers
    for (int i = 0; i < 15; ++i)
    {
        cb_push(&intCircBuf, &i);
    }

    //print to console
    printCircBuf(&intCircBuf);

    printf("Popping and pushing 99...\n");
    cb_pop(&intCircBuf);
    int rand = 99;
    cb_push(&intCircBuf, &rand);

    printCircBuf(&intCircBuf);

    cb_free(&intCircBuf);
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