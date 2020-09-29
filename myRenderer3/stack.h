#pragma once
#include "array.h"

class Stack {
public:
    Stack(int sizeElem);
    ~Stack();
    //void createNewStack();
    void push(void* srcData);
    void* peek();
    void pop();
private:
    Array m_Stack;
};
