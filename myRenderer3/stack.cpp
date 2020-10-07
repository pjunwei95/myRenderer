#include "stack.h"
#include <assert.h>
#include "logger.h"

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

void testStack()
{
    logmsg("test stack...\n");

    Stack<int>* s = new Stack<int>();
    int num = 1;
    s->push(&num);

    logmsg("peeking value = %d\n", *s->peek());

    s->pop();
    ++num;
    s->push(&num);
}