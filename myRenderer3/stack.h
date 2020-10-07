#pragma once
#include "array.h"

template <typename T>
class Stack {
public:
    Stack(int sizeElem);
    ~Stack();
    void push(void* srcData);
    void pop();
    T* peek();
    T* at(int index);
    uint32_t size();
private:
    Array<T> m_Stack;
};
