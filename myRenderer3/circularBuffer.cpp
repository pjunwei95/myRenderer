#include "circularBuffer.h"
#include <iostream>
#include "array.h"
#include "assert.h"

#define BUFFER_LENGTH 3

int front, back;

//A circular buffer is simply an array but with 2 cursors, front & back
//the cursors are simply index values
void c_init()
{
    front = 0;
    back = 0;
}

void c_read(const Array* const circBuf)
{
    int tempFront = front;
    printf("Reading..\n");
    for (int i = 0; i < BUFFER_LENGTH; ++i)
    {
        int idx = (tempFront + i) % BUFFER_LENGTH;
        void* ptr = (unsigned char*)circBuf->m_Data + (idx * circBuf->m_TypeSize);
        printf("%d ", *((int*)ptr));
    }
    printf("\n");
}

void c_push(Array* const array, const void* srcData)
{
    assert(array->m_Data);
    assert(srcData);

    //'push' a value directly into the 'back' slot
    //array[back] = value;
    void* element = a_at(array, back);
    memcpy(element, srcData, array->m_TypeSize);

    // Advances back
    back = (back + 1) % BUFFER_LENGTH;

    // When you 'pop', you simply move the 'front' cursor forward by one
    // Advances front to be always in front of back
    if (front == back)
    {
        front = (front + 1) % BUFFER_LENGTH;
    }
}

void testCircularBuffer()
{
    c_init();
    int empty = 0;
    //init fixed empty array
    Array intCircBuf = a_create_new_filled(BUFFER_LENGTH, &empty, sizeof(int));
    //Array doubleCircBuf = a_create_new_filled(BUFFER_LENGTH, &empty, sizeof(double));

    //push 10 numbers
    for (int i = 0; i < 10; ++i)
    {
        c_push(&intCircBuf, &i);
        //c_push(&doubleCircBuf, &i);
    }

    //print to console
    c_read(&intCircBuf);

    ////test double
    //void* ptr = (unsigned char*)doubleCircBuf.m_Data + (1 * doubleCircBuf.m_TypeSize);
    //printf("double[1] = %f\n", *((double*)ptr));
    
    a_free(&intCircBuf);
    //a_free(&doubleCircBuf);
}