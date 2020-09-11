#pragma once
#include "profiler.h"
#include <assert.h>

// A structure to represent a stack 
struct Stack {
    int top;
    unsigned capacity;
    Profile *array;
};

Stack * createStack(unsigned capacity);

bool isEmpty(Stack * stack);

void push(Stack * stack, Profile item);

void pop(Stack * stack);

Profile peek(Stack * stack);

struct Array {
    void* m_Data;
    int m_Size;
    int m_Capacity;
};

Array createNewArray() {
    Array a;
    a.m_Data = nullptr;
    a.m_Size = 0;
    a.m_Capacity = 0;
    return a;
};

void array_push(Array* const dstArr, const void* srcData, int sizeElem)
{
    assert(dstArr);
    assert(srcData);
    assert(sizeElem > 0);
    void* ptr = (unsigned char *) dstArr->m_Data + sizeElem * dstArr->m_Size;
    memcpy(ptr, srcData, sizeElem);
    dstArr->m_Size++;
}
