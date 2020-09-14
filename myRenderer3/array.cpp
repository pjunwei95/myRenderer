#include <assert.h>
#include <string.h>
#include "array.h"
#include "stdio.h"

#include <vector>

struct Array {
    void* m_Data; // pointer to array
    int m_Size; // number of elements
    int m_Capacity; // available memory size
    unsigned int m_typeSize; // size of element type
};

Array createNewArray(unsigned int sizeElem) {
    Array a;
    a.m_Data = nullptr;
    a.m_Size = 0;
    a.m_Capacity = 0;
    a.m_typeSize = sizeElem;
    return a;
}

bool a_empty(const Array* const dstArr)
{
    if (dstArr->m_Size > 0)
        return false;
    else
        return true;
}

void array_push(Array* const dstArr, const void* srcData, int sizeElem)
{
    assert(dstArr);
    assert(srcData);
    assert(sizeElem > 0);
    if (!dstArr->m_Data)
    {
        dstArr->m_Data = malloc(sizeElem);
        dstArr->m_Capacity++;
    }

    if (dstArr->m_Size == dstArr->m_Capacity)
    {
        dstArr->m_Capacity *= 2;
        dstArr->m_Data = realloc(dstArr->m_Data, dstArr->m_Capacity * sizeElem);
    }

    void* ptr = (unsigned char *)dstArr->m_Data + sizeElem * dstArr->m_Size;
    memcpy(ptr, srcData, sizeElem);
    dstArr->m_Size++;
}

void* a_front(const Array* const dstArr)
{
    assert(!a_empty(dstArr));
    assert(dstArr);
    assert(dstArr->m_Data);
    return (unsigned char*)dstArr->m_Data;
}

void* a_back(const Array* const dstArr)
{
    assert(!a_empty(dstArr));
    assert(dstArr);
    assert(dstArr->m_Data);
    int lastIdx = dstArr->m_Size - 1;
    return (unsigned char*)dstArr->m_Data + lastIdx * dstArr->m_typeSize;
}

void a_free(Array* const dstArr)
{
    assert(dstArr->m_Data);
    free(dstArr->m_Data);
}

void* a_at(const Array* const dstArr, int index)
{
    assert(index >= 0);
    assert(index < dstArr->m_Size);
    return (unsigned char*)dstArr->m_Data + index * dstArr->m_typeSize;
}

void testArray()
{
    //testing purposes
    //std::vector<char> test;
    //test.empty();

    Array a = createNewArray(sizeof(int));
    int num = 1;
    for (int i = 0; i < 10; ++i)
    {
        array_push(&a, &num, sizeof(int));
    }
    for (int i = 0; i < 10; ++i)
    {
        int numAtIdx = *((int*) a_at(&a, i));
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    
    int getFirst = *((int*) a_front(&a));

    printf("first = %d\n", getFirst);
    int getLast = *((int*)a_back(&a));
    printf("last = %d\n", getLast);
    a_free(&a);
}
