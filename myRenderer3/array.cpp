#include <assert.h>
#include <string.h>
#include "array.h"
#include "stdio.h"

#include <vector>

struct Array {
    void* m_Data; // pointer to array
    int m_Size; // number of elements
    int m_Capacity; //
    unsigned int m_typeSize;
};

Array createNewArray(unsigned int sizeElem) {
    Array a;
    a.m_Data = nullptr;
    a.m_Size = 0;
    a.m_Capacity = 0;
    a.m_typeSize = sizeElem;
    return a;
}

//void push_back(const T& value);

bool a_empty(Array* const dstArr)
{
    if (dstArr->m_Size > 0)
        return true;
    else
        return false;
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

    if (dstArr->m_Size >= dstArr->m_Capacity)
    {
        //capacity *= 2
        dstArr->m_Capacity *= 2;
        //copy over old memory
        dstArr->m_Data = realloc(dstArr->m_Data, dstArr->m_Capacity * sizeElem);
    }

    void* ptr = (unsigned char *)dstArr->m_Data + sizeElem * dstArr->m_Size;
    memcpy(ptr, srcData, sizeElem);
    dstArr->m_Size++;
    
}

void* a_front(const Array* const dstArr)
{
    assert(dstArr);
    assert(dstArr->m_Data);
    return (unsigned char*)dstArr->m_Data;
}

void* a_back(const Array* const dstArr)
{
    // TODO empty
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

//void a_init(Array* const dstArr)
//{
//
//}

void testArray()
{
    //testing purposes
    //std::vector<char> test;
    //test.empty();

    Array a = createNewArray(sizeof(int));
    int num = 1;
    int num2 = 2;
    array_push(&a, &num, sizeof(int));
    array_push(&a, &num2, sizeof(int));
    
    int getFirst = *((int*) a_front(&a));

    printf("first = %d\n", getFirst);
    int getSecond = *((int*)a_back(&a));
    printf("last = %d\n", getSecond);
    a_free(&a);
}
