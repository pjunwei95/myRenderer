#include "test.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>

#include "array.h"

#define BUFFER_LENGTH 3

Array createNewCircBuffer(unsigned int sizeElem)
{
    Array a;
    a.m_Data = malloc(BUFFER_LENGTH * sizeElem);
    a.m_Size = 0;
    a.m_Capacity = BUFFER_LENGTH;
    a.m_TypeSize = sizeElem;
    return a;
}

void pop(int* front, int* back)
{
    if (*front == *back)
    {
        printf("queue empty\n");
    }
    *front = (*front + 1) % (BUFFER_LENGTH);  // Advance the read pointer
}

void push(Array* array, int value, int* front, int* back)
{
    if (*front == (*back + 1) % BUFFER_LENGTH)
    {
        printf("queue full\n");
        pop(front, back);
    }
    //array[*back] = value;
    void* ptr = (unsigned char*)array->m_Data + (*back * array->m_TypeSize);
    memcpy(ptr, &value, array->m_TypeSize);
    *back = (*back + 1) % BUFFER_LENGTH;
}

void test()
{
    //Array a = createNewArray(sizeof(int));
    //int array[BUFFER_LENGTH] = { 1,2,3,4,5 };
    Array array = createNewCircBuffer(sizeof(int));
    int front = 0;
    int back = 0;

    push(&array, 6, &front, &back);
    push(&array, 7, &front, &back);
    push(&array, 8, &front, &back);
    push(&array, 9, &front, &back);
    push(&array, 10, &front, &back);
    push(&array, 11, &front, &back);
    ////reading
    //printf("Reading..\n");
    //for (int i = 0; i < BUFFER_LENGTH; ++i)
    //{
    //    printf("%d ", array[(front+i)%BUFFER_LENGTH]);
    //}
    //printf("\n");
}