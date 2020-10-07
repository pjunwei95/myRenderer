#include "stack.h"
#include <assert.h>

template <typename T>
Stack<T>::Stack(int sizeElem)
{
    m_Stack = new Array(sizeElem);
}

template <typename T>
Stack<T>::~Stack()
{
    delete m_Stack;
}

template <typename T>
void Stack<T>::push(void* srcData)
{
    m_Stack.pushBackArray(srcData);
}

template <typename T>
T* Stack<T>::peek()
{
    assert(!m_Stack.isArrayEmpty());
    return m_Stack.getArrayBack();
}

template <typename T>
void Stack<T>::pop()
{
    m_Stack.popBackArray();
}

template <typename T>
T* Stack<T>::at(int index)
{
    return m_Stack.getArrayAt(index);
}

template <typename T>
uint32_t Stack<T>::size()
{
    return m_Stack.getArraySize();
}