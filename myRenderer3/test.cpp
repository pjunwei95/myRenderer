#include "test.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include "array.h"
#include "assert.h"

#define BUFFER_LENGTH 3

int front, back;

void c_push(Array* const array, const void* srcData)
{
    //assert(array->m_Data);
    assert(srcData);
    //array[back] = value;
    void* element = a_at(array, back);
    memcpy(element, srcData, array->m_TypeSize);

    // Advances back
    back = (back + 1) % BUFFER_LENGTH;
    if (front == back)
    {
        front = (front + 1) % BUFFER_LENGTH;
    }
}

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

void test()
{
    c_init();
    int empty = 0;
    //init fixed empty array
    Array circBuf = a_create_new_filled(BUFFER_LENGTH, &empty, sizeof(int));


    for (int i = 0; i < 10; ++i)
    {
        c_push(&circBuf, &i);
    }

    c_read(&circBuf);
}