#include "circularBuffer.h"
#include <iostream>
#include "assert.h"

#define BUFFER_LENGTH 3

void printCircBuf(const CircularBuffer* const cb);

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
CircularBuffer createNewCircBuf(unsigned int bufferLength, const void* const elemVal, unsigned int sizeElem)
{
    CircularBuffer cb;
    cb.m_Array = createNewFilledArray(bufferLength, elemVal, sizeElem);
    cb.m_Buffer_Length = bufferLength;
    cb.m_Front = 0;
    cb.m_Back = 0;
    return cb;
}

//front()
//back()
//size()
//empty()
//full()
//push_back()
//push_front()
//pop_back()
//pop_front()
//clear()

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
    return getArraySize(&cb->m_Array);
}

bool isCircBufEmpty(const CircularBuffer* const cb)
{
    return isArrayEmpty(&cb->m_Array);
}

bool isCircBufFull(const CircularBuffer* const cb)
{
    return getArraySize(&cb->m_Array) >= getArrayCapacity(&cb->m_Array);
}

void pushFrontCircBuf(CircularBuffer* const cb, const void* srcData)
{
    assert(!isCircBufFull(cb));
    // buffer[front]
    void* addressAtFront = getArrayAt(&cb->m_Array, cb->m_Front);
    memcpy(addressAtFront, srcData, getArrayTypeSize(&cb->m_Array));
    addArraySize(&cb->m_Array, 1);

    cb->m_Front = (cb->m_Front + 1) % cb->m_Buffer_Length;
    
    //if(cb->m_Front == cb->m_Back)
}

void popBackCircBuf(CircularBuffer* const cb)
{
    assert(!isCircBufEmpty(cb));
    void* addressAtBack = getArrayAt(&cb->m_Array, cb->m_Back);
    cb->m_Back = (cb->m_Back + 1) % cb->m_Buffer_Length;
}

//void popCircBuf(CircularBuffer* const cb)
//{
//    assert(cb->m_Array.m_Data);
//    if (cb->m_Front == cb->m_Back)
//    {
//        cb->m_Front = (cb->m_Front + 1) % cb->m_Buffer_Length;
//    }
//}
//
////Assuming fixed size buffer
//void pushCircBuf(CircularBuffer* const cb, const void* srcData)
//{
//    assert(cb->m_Array.m_Data);
//    assert(srcData);
//    assert(cb->m_Array.m_Size <= cb->m_Array.m_Capacity);//check for indices instead
//
//    //'push' a value directly into the 'back' slot
//    void* dstIdx = getArrayAt(&cb->m_Array, cb->m_Back);
//    //array[back] = srcData;
//    memcpy(dstIdx, srcData, cb->m_Array.m_TypeSize);
//
//    // When you 'pop', you simply move the 'front' cursor forward by one
//    // Advances front to be always in front of back
//    popCircBuf(cb);
//
//    // Advances back
//    cb->m_Back = (cb->m_Back + 1) % cb->m_Buffer_Length;
//}
//
//void freeCircBuf(CircularBuffer* const cb)
//{
//    assert(cb);
//    freeArray(&cb->m_Array);
//}
//
//void testCircularBuffer()
//{
//    int empty = 0;
//    CircularBuffer intCircBuf = createNewCircBuf(3, &empty, sizeof(int));
//
//    //push 10 numbers
//    for (int i = 0; i < 15; ++i)
//    {
//        pushCircBuf(&intCircBuf, &i);
//    }
//
//    //print to console
//    printCircBuf(&intCircBuf);
//
//    printf("Popping and pushing 99...\n");
//    popCircBuf(&intCircBuf);
//    int rand = 99;
//    pushCircBuf(&intCircBuf, &rand);
//
//    printCircBuf(&intCircBuf);
//
//    freeCircBuf(&intCircBuf);
//}

void printCircBuf(const CircularBuffer* const cb)
{
    int tempFront = cb->m_Front;
    printf("Reading..\n");
    for (int i = 0; i < cb->m_Buffer_Length; ++i)
    {
        int idx = (tempFront + i) % cb->m_Buffer_Length;
        void* ptr = (unsigned char*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        printf("%d ", *((int*)ptr));
    }
    printf("\n");
}