#include <assert.h>
#include <string.h>
#include "array.h"
#include "stdio.h"

#include <vector>

struct Array {
    void* m_Data; // pointer to array
    int m_Size; // number of elements
    int m_Capacity; // available memory size
    unsigned int m_TypeSize; // size of element type
};

Array createNewArray(unsigned int sizeElem) {
    Array a;
    a.m_Data = nullptr;
    a.m_Size = 0;
    a.m_Capacity = 0;
    a.m_TypeSize = sizeElem;
    return a;
}

bool a_empty(const Array* const dstArr)
{
    return (dstArr->m_Size > 0) ? false : true;
}

int a_size(const Array* const arr)
{
    return arr->m_Size;
}

void* a_realloc(void* block, size_t oldSize, size_t newSize)
{
    assert(block);
    assert(oldSize < newSize);
    void* newBlock;
    newBlock = malloc(newSize);
    assert(newBlock);
    newBlock = memcpy(newBlock, block, oldSize);
    free(block);
    return newBlock;
}

void array_push(Array* const dstArr, const void* srcData, int sizeElem)
{
    assert(dstArr);
    assert(srcData);
    assert(sizeElem > 0);
    void* ptr;
    if (!dstArr->m_Data)
    {
        ptr = malloc(sizeElem);
        assert(ptr);
        dstArr->m_Data = ptr;
        dstArr->m_Capacity++;
    }

    if (dstArr->m_Size == dstArr->m_Capacity)
    {
        /*dstArr->m_Capacity *= 2;
        ptr = realloc(dstArr->m_Data, dstArr->m_Capacity * sizeElem);*/
        ptr = a_realloc(dstArr->m_Data, dstArr->m_Capacity * sizeElem, dstArr->m_Capacity * sizeElem * 2);
        dstArr->m_Capacity *= 2;

        assert(ptr);
        dstArr->m_Data = ptr;
    }
    ptr = (unsigned char *)dstArr->m_Data + sizeElem * dstArr->m_Size;
    memcpy(ptr, srcData, sizeElem);
    dstArr->m_Size++;
}

void* a_front(const Array* const arr)
{
    assert(!a_empty(arr));
    assert(arr);
    assert(arr->m_Data);
    return (unsigned char*)arr->m_Data;
}

void* a_back(const Array* const arr)
{
    assert(!a_empty(arr));
    assert(arr->m_Data);
    int lastIdx = arr->m_Size - 1;
    return (unsigned char*)arr->m_Data + lastIdx * arr->m_TypeSize;
}

void a_free(Array* const dstArr)
{
    assert(dstArr->m_Data);
    free(dstArr->m_Data);
}

void* a_at(const Array* const arr, int index)
{
    assert(!a_empty(arr));
    assert(arr->m_Data);
    assert(index >= 0);
    assert(index < arr->m_Size);
    return (unsigned char*)arr->m_Data + index * arr->m_TypeSize;
}

void testArray()
{
    Array a = createNewArray(sizeof(int));
    int num = 1;
    
    //push 10 elements and print
    for (int i = 0; i < 10; ++i)
    {
        array_push(&a, &num, sizeof(int));
        num++;
    }
    for (int i = 0; i < 10; ++i)
    {
        int numAtIdx = *((int*) a_at(&a, i));
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    
    //print first
    int getFirst = *((int*) a_front(&a));
    printf("first = %d\n", getFirst);

    //print last
    int getLast = *((int*)a_back(&a));
    printf("last = %d\n", getLast);

    //free after usage
    a_free(&a);
}
