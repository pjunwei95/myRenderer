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

template <typename T>
Stack<T>::Stack()
{
    m_Stack = new Array<T>();
}

template <typename T>
Stack<T>::~Stack()
{
    delete m_Stack;
}

template <typename T>
void Stack<T>::push(T* srcData)
{
    m_Stack->pushBackArray(srcData);
}

template <typename T>
T* Stack<T>::peek()
{
    assert(!m_Stack->isArrayEmpty());
    return m_Stack->getArrayBack();
}

template <typename T>
void Stack<T>::pop()
{
    m_Stack->popBackArray();
}

template <typename T>
T* Stack<T>::at(uint32_t index)
{
    return m_Stack->getArrayAt(index);
}

template <typename T>
uint32_t Stack<T>::size()
{
    return m_Stack->getArraySize();
}

