#include "stack.h"
#include <assert.h>

Stack::Stack(int sizeElem)
{
    m_Stack = createNewArray(sizeElem);
}

Stack::~Stack()
{
    freeArray(&m_Stack);
    delete &m_Stack;
}

void Stack::Push(void* srcData)
{
    pushBackArray(&m_Stack, srcData);
}

void* Stack::Peek()
{
    assert(!isArrayEmpty(&m_Stack));
    return getArrayBack(&m_Stack);
}

void Stack::Pop()
{
    popBackArray(&m_Stack);
}

void* Stack::At(int index)
{
    return getArrayAt(&m_Stack, index);
}

int Stack::Size() 
{
    return getArraySize(&m_Stack);
}