#pragma once
#include "array.h"

class Stack {
public:
    Stack(int sizeElem);
    ~Stack();
    //void createNewStack();
    void Push(void* srcData);
    void* Peek();
    void Pop();
    void* At(int index);
    int Size();
private:
    Array m_Stack;
};
