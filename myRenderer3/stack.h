#pragma once
#include "array.h"

void testStack();

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    void push(T* srcData);
    void pop();
    T* peek();
    T* at(uint32_t index);
    uint32_t size();
private:
    Array<T>* m_Stack;
};
