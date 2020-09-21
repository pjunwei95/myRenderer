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
    cb.array = a_create_new_filled(BUFFER_LENGTH, elemVal, sizeElem);
    cb.front = 0;
    cb.back = 0;
    return cb;
}

void cb_pop(CircularBuffer* const cb)
{
    assert(cb->array.m_Data);
    if (cb->front == cb->back)
    {
        cb->front = (cb->front + 1) % BUFFER_LENGTH;
    }
}

//Assuming fixed size buffer
void cb_push(CircularBuffer* const cb, const void* srcData)
{
    assert(cb->array.m_Data);
    assert(srcData);
    assert(cb->array.m_Size < cb->array.m_Capacity);

    //'push' a value directly into the 'back' slot
    void* dstIdx = a_at(&cb->array, cb->back);
    //array[back] = srcData;
    memcpy(dstIdx, srcData, cb->array.m_TypeSize);

    // When you 'pop', you simply move the 'front' cursor forward by one
    // Advances front to be always in front of back
    cb_pop(cb);

    // Advances back
    cb->back = (cb->back + 1) % BUFFER_LENGTH;
}

void cb_free(CircularBuffer* const cb)
{
    a_free(&cb->array);
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
    int tempFront = cb->front;
    printf("Reading..\n");
    for (int i = 0; i < BUFFER_LENGTH; ++i)
    {
        int idx = (tempFront + i) % BUFFER_LENGTH;
        void* ptr = (unsigned char*)cb->array.m_Data + (idx * cb->array.m_TypeSize);
        printf("%d ", *((int*)ptr));
    }
    printf("\n");
}