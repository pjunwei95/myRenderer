#pragma once
#include "array.h"

class Stack {
public:
    Stack(int sizeElem);
    ~Stack();
    void push(void* srcData);
    void* peek();
    void pop();
    void* at(int index);
    int size();
private:
    Array m_Stack;
};
