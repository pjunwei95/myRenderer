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

bool a_empty(const Array* const arr)
{
    assert(arr);
    return (arr->m_Size > 0) ? false : true;
}

int a_size(const Array* const arr)
{
    assert(arr);
    return arr->m_Size;
}

int a_capacity(const Array* const arr)
{
    assert(arr);
    return arr->m_Capacity;
}

void a_clear(Array* const arr)
{
    assert(arr);
    arr->m_Size = 0;
}
void* a_front(const Array* const arr)
{
    assert(arr);
    assert(!a_empty(arr));
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

static void* a_realloc(void* block, size_t oldSize, size_t newSize)
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

void check_suff_mem(Array *const dstArr, void * ptr)
{
    assert(dstArr);
    assert(ptr);
    if (!dstArr->m_Data) // array memory uninitialised
    {
        ptr = malloc(dstArr->m_TypeSize);
        assert(ptr);
        dstArr->m_Data = ptr;
        dstArr->m_Capacity++;
    }
    else if (dstArr->m_Size == dstArr->m_Capacity) // array memory exceeded
    {
        // *Block, oldSize, newSize
        ptr = a_realloc(dstArr->m_Data, dstArr->m_Capacity * dstArr->m_TypeSize, dstArr->m_Capacity * dstArr->m_TypeSize * 2);
        assert(ptr);
        dstArr->m_Data = ptr;
        dstArr->m_Capacity *= 2;
    }
}

void a_push_back(Array* const dstArr, const void* srcData)
{
    assert(dstArr);
    assert(srcData);
    assert(dstArr->m_TypeSize > 0);
    void* ptr;
    check_suff_mem(dstArr, &ptr);
    ptr = (unsigned char *)dstArr->m_Data + dstArr->m_TypeSize * dstArr->m_Size;
    memcpy(ptr, srcData, dstArr->m_TypeSize);
    dstArr->m_Size++;
}

void a_pop_back(Array* const arr)
{
    assert(arr);
    assert(!a_empty(arr));
    arr->m_Size--;
}



void a_erase(Array* const arr, int index)
{
    assert(!a_empty(arr));
    assert(index >= 0 && index < arr->m_Size);
    if (index == arr->m_Size - 1) // last index
        a_pop_back(arr);
    //shift array left
    unsigned char* ptr = (unsigned char*)arr->m_Data;
    // A[i] = *[A + i]
    for (unsigned char* i = ptr + index; i < ptr + (arr->m_Size - 1) * arr->m_TypeSize; i += arr->m_TypeSize)
    {
        // A[i] = A[i+1]
        memcpy(i, i + arr->m_TypeSize, arr->m_TypeSize);
    }
    arr->m_Size--;
}

void testArray()
{
    Array a = createNewArray(sizeof(int));
    int num = 0;
    int numAtIdx;
    //push 10 elements and print
    for (int i = 0; i < 10; ++i)
    {
        a_push_back(&a, &num);
        num++;
        numAtIdx = *((int*)a_at(&a, i));
        printf("array [%d] = %d\n", i, numAtIdx);
    }

    //print first
    int getFirst = *((int*)a_front(&a));
    printf("first = %d\n", getFirst);

    //erase at idx
    printf("erasing a[%d] = %d...\n", 6, *((int*)a_at(&a, 6) ));

    a_erase(&a, 6);
    printf("a[%d] is now = %d\n", 6, *((int*)a_at(&a, 6) ) );

    //remove last
    printf("popping last element...\n");
    a_pop_back(&a);

    //print last
    int getLast = *((int*)a_back(&a));
    printf("last = %d\n", getLast);

    //clears array
    a_clear(&a);

    //print first
    /*int getFirst = *((int*)a_front(&a));
    printf("first = %d\n", getFirst);*/

    //free after usage
    a_free(&a);
}
