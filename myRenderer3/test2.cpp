#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdint.h>
#include "test2.h"
#include "logger.h"

//template<typename T>
//class Array {
//private:
//    void* m_Data; // pointer to array
//    unsigned int m_Size; // number of elements
//    unsigned int m_Capacity; // available memory size
//    unsigned int m_TypeSize; // size of element type
//public:
//    Array(uint32_t sizeElem)
//        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }, m_TypeSize{ sizeElem }
//    {}
//
//    bool isArrayEmpty(const Array* const arr);
//
//};


//// Function that takes in capacity that returns you 
//// an Array with the appropriate size & capacity
//Array Array::createNewFilledArray(unsigned int numElem, unsigned int sizeElem)
//{
//    assert(sizeElem);
//    Array a;
//    a.m_Data = malloc(numElem * sizeElem);
//    assert(a.m_Data);
//
//    a.m_Size = 0;
//    a.m_Capacity = numElem;
//    a.m_TypeSize = sizeElem;
//
//    return a;
//}
//
template<typename T>
bool Array<T>::isArrayEmpty() const
{
    assert(m_Data);
    return 0 == m_Size;
}

template<typename T>
int Array<T>::getArraySize() const
{
    assert(m_Data);
    return m_Size;
}

template<typename T>
void Array<T>::addArraySize(int increment)
{
    assert(m_Data);
    assert(increment);
    m_Size += increment;
}

template<typename T>
int Array<T>::getArrayCapacity() const
{
    assert(m_Data);
    return m_Capacity;
}

template<typename T>
int Array<T>::getArrayTypeSize() const
{
    assert(m_Data);
    return m_TypeSize;
}

template<typename T>
void Array<T>::clearArray()
{
    assert(m_Data);
    m_Size = 0;
}

template<typename T>
T* Array<T>::getArrayFront() const
{
    assert(!isArrayEmpty());
    assert(m_Data);
    return (T*)m_Data;
}
//
//void* Array::getArrayBack(const Array* const arr)
//{
//    assert(!isArrayEmpty(arr));
//    assert(arr->m_Data);
//    int lastIdx = arr->m_Size - 1;
//    return (unsigned char*)arr->m_Data + lastIdx * arr->m_TypeSize;
//}

//void Array::freeArray(Array* const dstArr)
//{
//    assert(dstArr->m_Data);
//    free(dstArr->m_Data);
//}
//
template<typename T>
T* Array<T>::getArrayAt(uint32_t index) const
{
    assert(!isArrayEmpty());
    assert(m_Data);
    assert(index < m_Size);
    return (T*)((uint8_t*)m_Data + index * m_TypeSize);
}

template<typename T>
void Array<T>::popBackArray()
{
    assert(!isArrayEmpty());
    m_Size--;
}

template<typename T>
void* Array<T>::reallocArray(void* block, size_t oldSize, size_t newSize)
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

template<typename T>
void Array<T>::checkArraySuffMem(void* ptr)
{
    //assert(dstArr);
    assert(ptr);
    if (!m_Data) // array memory uninitialised
    {
        ptr = malloc(m_TypeSize);
        assert(ptr);
        m_Data = ptr;
        m_Capacity++;
    }
    else if (m_Size == m_Capacity) // array memory exceeded
    {
        // *Block, oldSize, newSize
        ptr = reallocArray(m_Data, m_Capacity * m_TypeSize, m_Capacity * m_TypeSize * 2);
        assert(ptr);
        m_Data = ptr;
        m_Capacity *= 2;
    }
}

template<typename T>
void Array<T>::pushBackArray(const T* srcData)
{
    //assert(dstArr);
    assert(srcData);
    //assert(dstArr->m_TypeSize > 0);
    assert(m_TypeSize > 0);
    assert(m_TypeSize == sizeof(*srcData));
    void* ptr;
    checkArraySuffMem(&ptr);
    ptr = (unsigned char *)m_Data + m_TypeSize * m_Size;
    memcpy(ptr, srcData, m_TypeSize);
    m_Size++;
}

//void Array::insertArray(Array* const dstArr, unsigned int index, const void* srcData)
//{
//    assert(dstArr);
//    assert(srcData);
//    assert(index >= 0 && index <= dstArr->m_Size);
//    void* ptr;
//    checkArraySuffMem(dstArr, &ptr);
//    unsigned char* newPtr = (unsigned char*)dstArr->m_Data;
//    //shift array right
//    // for i = size-1; i > index-1; i--
//    for (unsigned char* i = newPtr + (dstArr->m_Size - 1) * dstArr->m_TypeSize;
//        i > newPtr + (index - 1) * dstArr->m_TypeSize;
//        i -= dstArr->m_TypeSize)
//    {
//        //A[i+1] = A[i]
//        memcpy(i + dstArr->m_TypeSize, i, dstArr->m_TypeSize);
//    }
//    //A[index] = data
//    memcpy(newPtr + index * dstArr->m_TypeSize, srcData, dstArr->m_TypeSize);
//    dstArr->m_Size++;
//}

template<typename T>
void Array<T>::eraseArrayAt(uint32_t index)
{
    assert(!isArrayEmpty());
    assert(index < m_Size);
    if (index == m_Size - 1) // last index
    {
        popBackArray(); //CHECK SIZE
        return;
    }
    ////shift array left
    //unsigned char* ptr = (unsigned char*)m_Data;
    //// A[i] = *[A + i]
    //// for i = index; i < size-1; i++
    //for (unsigned char* i = ptr + index * arr->m_TypeSize;
    //    i < ptr + (arr->m_Size - 1) * arr->m_TypeSize;
    //    i += arr->m_TypeSize)
    //{
    //    // A[i] = A[i+1]
    //    memcpy(i, i + arr->m_TypeSize, arr->m_TypeSize);
    //}

    //shift array left
    // for i = index; i < size-1; i++
    for (uint32_t i = 0; i < m_Size - 1; ++i)
    {
        uint8_t* ptr = (uint8_t*)m_Data + (index + i) * m_TypeSize;
        // A[i] = A[i+1]
        memcpy(ptr, ptr + m_TypeSize, m_TypeSize);
    }
    m_Size--;
}

//// This method will remove the element at the specified index but
//// will not preserve the order in the array(the element is swapped with
//// the last one of the array)
//void Array<T>::removeAtFastArray(Array* const arr, unsigned int index)
//{
//    assert(!isArrayEmpty(arr));
//    assert(index >= 0 && index < arr->m_Size);
//    unsigned char* ptr = (unsigned char*)arr->m_Data;
//    unsigned char* ptrToLast = ptr + (arr->m_Size - 1) * arr->m_TypeSize;
//    unsigned char* ptrToIdx = ptr + index * arr->m_TypeSize;
//    memcpy(ptrToIdx, ptrToLast, arr->m_TypeSize);
//    arr->m_Size--;
//}

void testArray2()
{
    //Array a = createNewArray(sizeof(int));
    Array<int>* a = new Array<int>();
    int num = 1;
    //a->pushBackArray(&num);
    //logmsg("empty? %d\n", a->isArrayEmpty());
    //push 10 elements and print (init)
    for (int i = 0; i < 10; ++i)
    {
        a->pushBackArray(&num);
        num++;
    }
    //printTestArray(&a);
    a->printTestArray();

    //print first
    //int getFirst = *((int*)getArrayFront(&a));
    int getFirst = *a->getArrayFront();
    printf("first = %d\n", getFirst);

    //erase at idx
    printf("erasing a[%d] = %d...\n", 6, *a->getArrayAt(6));
    a->eraseArrayAt(6);
    printf("a[%d] is now = %d\n", 6, *a->getArrayAt(6));

    ////insert at idx
    //int newNum = 99;
    //printf("inserting a[%d] = %d...\n", 6, newNum);
    //insertArray(&a, 6, &newNum);
    //printf("a[%d] is now = %d\n", 6, *((int*)getArrayAt(&a, 6)));

    //printTestArray(&a);
    ////remove at fast idx 5
    //printf("RemoveAtFast 5...\n");
    //removeAtFastArray(&a, 5);

    //printTestArray(&a);

    ////remove last
    //printf("popping last element...\n");
    //popBackArray(&a);

    ////print last
    //int getLast = *((int*)getArrayBack(&a));
    //printf("last = %d\n", getLast);

    ////clears array
    //clearArray(&a);

    ////print first
    ///*int getFirst = *((int*)a_front(&a));
    //printf("first = %d\n", getFirst);*/

    ////free after usage
    //freeArray(&a);
}

template<typename T>
void Array<T>::printTestArray()
{
    printf("==============\n");
    printf("printing updated table\n");
    int numAtIdx;
    for (uint32_t i = 0; i < m_Size; ++i)
    {
        //numAtIdx = *((int*)getArrayAt(a, i));
        numAtIdx = *getArrayAt(i);
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    printf("==============\n");
}
