#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "stdio.h"

void printTestArray(const Array* const a);

Array createNewArray(unsigned int sizeElem) 
{
    Array a;
    a.m_Data = nullptr;
    a.m_Size = 0;
    a.m_Capacity = 0;
    a.m_TypeSize = sizeElem;
    return a;
}

// Function that takes in capacity that returns you 
// an Array with the appropriate size & capacity
Array createNewFilledArray(unsigned int numElem, const void* const elemVal, unsigned int sizeElem)
{
    assert(elemVal);
    assert(sizeElem);
    Array a;
    a.m_Data = malloc(numElem * sizeElem);
    assert(a.m_Data);
    a.m_Size = numElem;
    a.m_Capacity = numElem;
    a.m_TypeSize = sizeElem;

    for (unsigned int i = 0; i < numElem; ++i)
    {
        unsigned char* ptr = (unsigned char*)a.m_Data + (i * sizeElem);
        memcpy(ptr, elemVal, sizeElem);
    }
    return a;
}

bool isArrayEmpty(const Array* const arr)
{
    assert(arr);
    return 0 == arr->m_Size;
}

int getArraySize(const Array* const arr)
{
    assert(arr);
    return arr->m_Size;
}

int getArrayCapacity(const Array* const arr)
{
    assert(arr);
    return arr->m_Capacity;
}

void clearArray(Array* const arr)
{
    assert(arr);
    arr->m_Size = 0;
}

void* getArrayFront(const Array* const arr)
{
    assert(arr);
    assert(!isArrayEmpty(arr));
    assert(arr->m_Data);
    return (unsigned char*)arr->m_Data;
}

void* getArrayBack(const Array* const arr)
{
    assert(!isArrayEmpty(arr));
    assert(arr->m_Data);
    int lastIdx = arr->m_Size - 1;
    return (unsigned char*)arr->m_Data + lastIdx * arr->m_TypeSize;
}

void freeArray(Array* const dstArr)
{
    assert(dstArr->m_Data);
    free(dstArr->m_Data);
}

void* getArrayAt(const Array* const arr, unsigned int index)
{
    assert(!isArrayEmpty(arr));
    assert(arr->m_Data);
    assert(index >= 0);
    assert(index < arr->m_Size);
    return (unsigned char*)arr->m_Data + index * arr->m_TypeSize;
}

void popBackArray(Array* const arr)
{
    assert(arr);
    assert(!isArrayEmpty(arr));
    arr->m_Size--;
}

static void* reallocArray(void* block, size_t oldSize, size_t newSize)
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

void checkArraySuffMem(Array *const dstArr, void * ptr)
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
        ptr = reallocArray(dstArr->m_Data, dstArr->m_Capacity * dstArr->m_TypeSize, dstArr->m_Capacity * dstArr->m_TypeSize * 2);
        assert(ptr);
        dstArr->m_Data = ptr;
        dstArr->m_Capacity *= 2;
    }
}

void pushBackArray(Array* const dstArr, const void* srcData)
{
    assert(dstArr);
    assert(srcData);
    assert(dstArr->m_TypeSize > 0);
    void* ptr;
    checkArraySuffMem(dstArr, &ptr);
    ptr = (unsigned char *)dstArr->m_Data + dstArr->m_TypeSize * dstArr->m_Size;
    memcpy(ptr, srcData, dstArr->m_TypeSize);
    dstArr->m_Size++;
}

void insertArray(Array* const dstArr, unsigned int index, const void* srcData)
{
    assert(dstArr);
    assert(srcData);
    assert(index >= 0 && index <= dstArr->m_Size);
    void* ptr;
    checkArraySuffMem(dstArr, &ptr);
    unsigned char* newPtr = (unsigned char*)dstArr->m_Data;
    //shift array right
    // for i = size-1; i > index-1; i--
    for (unsigned char* i = newPtr + (dstArr->m_Size - 1) * dstArr->m_TypeSize; 
        i > newPtr + (index - 1) * dstArr->m_TypeSize; 
        i -= dstArr->m_TypeSize)
    {
        //A[i+1] = A[i]
        memcpy(i + dstArr->m_TypeSize, i, dstArr->m_TypeSize);
    }
    //A[index] = data
    memcpy(newPtr + index * dstArr->m_TypeSize, srcData, dstArr->m_TypeSize);
    dstArr->m_Size++;
}

void eraseArrayAt(Array* const arr, unsigned int index)
{
    assert(!isArrayEmpty(arr));
    assert(index >= 0 && index < arr->m_Size);
    if (index == arr->m_Size - 1) // last index
    {
        popBackArray(arr); //CHECK SIZE
        return;
    }
    //shift array left
    unsigned char* ptr = (unsigned char*)arr->m_Data;
    // A[i] = *[A + i]
    // for i = index; i < size-1; i++
    for (unsigned char* i = ptr + index * arr->m_TypeSize; 
        i < ptr + (arr->m_Size - 1) * arr->m_TypeSize; 
        i += arr->m_TypeSize)
    {
        // A[i] = A[i+1]
        memcpy(i, i + arr->m_TypeSize, arr->m_TypeSize);
    }
    arr->m_Size--;
}

// This method will remove the element at the specified index but
// will not preserve the order in the array(the element is swapped with
// the last one of the array)
void removeAtFastArray(Array* const arr, unsigned int index)
{
    assert(!isArrayEmpty(arr));
    assert(index >= 0 && index < arr->m_Size);
    unsigned char* ptr = (unsigned char*)arr->m_Data;
    unsigned char* ptrToLast = ptr + (arr->m_Size - 1) * arr->m_TypeSize;
    unsigned char* ptrToIdx = ptr + index * arr->m_TypeSize;
    memcpy(ptrToIdx, ptrToLast, arr->m_TypeSize);
    arr->m_Size--;
}

void testArray()
{
    Array a = createNewArray(sizeof(int));
    int num = 0;
    //push 10 elements and print (init)
    for (int i = 0; i < 10; ++i)
    {
        pushBackArray(&a, &num);
        num++;
    }
    printTestArray(&a);

    //print first
    int getFirst = *((int*)getArrayFront(&a));
    printf("first = %d\n", getFirst);

    //erase at idx
    printf("erasing a[%d] = %d...\n", 6, *((int*)getArrayAt(&a, 6) ));
    eraseArrayAt(&a, 6);
    printf("a[%d] is now = %d\n", 6, *((int*)getArrayAt(&a, 6) ) );

    //insert at idx
    int newNum = 99;
    printf("inserting a[%d] = %d...\n", 6, newNum);
    insertArray(&a, 6, &newNum);
    printf("a[%d] is now = %d\n", 6, *((int*)getArrayAt(&a, 6)));
    
    printTestArray(&a);
    //remove at fast idx 5
    printf("RemoveAtFast 5...\n");
    removeAtFastArray(&a, 5);

    printTestArray(&a);

    //remove last
    printf("popping last element...\n");
    popBackArray(&a);

    //print last
    int getLast = *((int*)getArrayBack(&a));
    printf("last = %d\n", getLast);

    //clears array
    clearArray(&a);

    //print first
    /*int getFirst = *((int*)a_front(&a));
    printf("first = %d\n", getFirst);*/

    //free after usage
    freeArray(&a);
}

void printTestArray(const Array* const a)
{
    printf("==============\n");
    printf("printing updated table\n");
    int numAtIdx;
    for (unsigned int i = 0; i < a->m_Size; ++i)
    {
        numAtIdx = *((int*)getArrayAt(a, i));
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    printf("==============\n");
}
