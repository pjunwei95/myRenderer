#include "stack.h"

Stack::Stack(int sizeElem)
{
    m_Stack = createNewArray(sizeElem);
}

Stack::~Stack()
{
    freeArray(&m_Stack);
}

void Stack::push(void* srcData)
{
    pushBackArray(&m_Stack, srcData);
}

void* Stack::peek()
{
    return getArrayBack(&m_Stack);
}
void Stack::pop()
{
    popBackArray(&m_Stack);
}
