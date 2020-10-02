#include "stack.h"
#include <assert.h>

Stack::Stack(int sizeElem)
{
    m_Stack = createNewArray(sizeElem);
}

Stack::~Stack()
{
}

void Stack::push(void* srcData)
{
    pushBackArray(&m_Stack, srcData);
}

void* Stack::peek()
{
    assert(!isArrayEmpty(&m_Stack));
    return getArrayBack(&m_Stack);
}

void Stack::pop()
{
    popBackArray(&m_Stack);
}

void* Stack::at(int index)
{
    return getArrayAt(&m_Stack, index);
}

int Stack::size() 
{
    return getArraySize(&m_Stack);
}
void Stack::free()
{
    freeArray(&m_Stack);
    delete &m_Stack;
}