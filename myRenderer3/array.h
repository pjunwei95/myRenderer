#pragma once
#include <stdint.h>
#include <assert.h>
#include "stdio.h"


template<typename T>
class Array {
private:
    T* m_Data; // pointer to array
    uint32_t m_Size; // number of elements
    uint32_t m_Capacity; // available memory size

    //deprecated
    //uint32_t m_TypeSize; // size of element type

    void checkArraySuffMem();
public:
    Array();
    // new filled array of fixed size
    Array(uint32_t numElem);
    ~Array();
    
    bool isArrayEmpty() const;
    void addArraySize(int increment);
    uint32_t getArraySize() const;
    uint32_t getArrayCapacity() const;
    T* getArrayFront() const;
    T* getArrayBack() const;
    T* getArrayAt(uint32_t index) const;
    void pushBackArray(const T* srcData);
    void popBackArray();
    void eraseArrayAt(uint32_t index);
    void insertArray(uint32_t index, const T* srcData);
    void clearArray();
    void removeAtFastArray(uint32_t index);
    void printTestArray();

    //DEPRECATED
    //Array createNewArray(unsigned int sizeElem);

    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);

    //void* reallocArray(void* block, size_t oldSize, size_t newSize);

    //int getArrayTypeSize() const;

    //void freeArray();

};




template<typename T>
Array<T>::Array()
    : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 } {}

// new filled array of fixed size
template<typename T>
Array<T>::Array(uint32_t numElem)
    : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ numElem }
{
    m_Data = new T[numElem];
    assert(m_Data);
}

template<typename T>
Array<T>::~Array()
{
    assert(m_Data);
    delete[] m_Data;
    m_Data = nullptr;
    assert(!m_Data);
}

template<typename T>
bool Array<T>::isArrayEmpty() const
{
    assert(m_Data);
    return 0 == m_Size;
}

template<typename T>
uint32_t Array<T>::getArraySize() const
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
uint32_t Array<T>::getArrayCapacity() const
{
    assert(m_Data);
    return m_Capacity;
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
    return &m_Data[0];
}

template<typename T>
T* Array<T>::getArrayBack() const
{
    assert(!isArrayEmpty());
    assert(m_Data);
    return &m_Data[m_Size - 1];
}

template<typename T>
T* Array<T>::getArrayAt(uint32_t index) const
{
    assert(!isArrayEmpty());
    assert(m_Data);
    assert(index < m_Size);
    return &m_Data[index];
}

template<typename T>
void Array<T>::popBackArray()
{
    assert(!isArrayEmpty());
    m_Size--;
}

template<typename T>
void Array<T>::checkArraySuffMem()
{
    if (!m_Data) // array memory uninitialised
    {
        m_Capacity++;
        m_Data = new T[m_Capacity];
    }
    else if (m_Size == m_Capacity) // array memory exceeded
    {
        m_Capacity *= 2;
        T* temp = new T[m_Capacity];
        for (uint32_t i = 0; i < m_Size; ++i)
            temp[i] = m_Data[i];

        delete[] m_Data;
        m_Data = temp;

    }
}

template<typename T>
void Array<T>::pushBackArray(const T* srcData)
{
    assert(srcData);
    checkArraySuffMem();
    assert(m_Size < m_Capacity);
    m_Data[m_Size] = *srcData;
    m_Size++;
}

template<typename T>
void Array<T>::insertArray(uint32_t index, const T* srcData)
{
    assert(srcData);
    assert(index <= m_Size);

    checkArraySuffMem();
    //shift array right
    // for i = size-1; i > index-1; i--
    for (uint32_t i = m_Size - 1; i > index - 1; --i)
        m_Data[i + 1] = m_Data[i];
    m_Data[index] = *srcData;
    m_Size++;
}

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
    //shift array left
    // for i = index; i < size-1; i++
    //    A[i] = A[i+1]
    for (uint32_t i = index; i < m_Size - 1; ++i)
        m_Data[i] = m_Data[i + 1];
    m_Size--;
}

// This method will remove the element at the specified index but
// will not preserve the order in the array(the element is swapped with
// the last one of the array)
template<typename T>
void Array<T>::removeAtFastArray(uint32_t index)
{
    assert(!isArrayEmpty());
    assert(index < m_Size);
    m_Data[index] = *getArrayBack();
    m_Size--;
}

template<typename T>
void Array<T>::printTestArray()
{
    printf("==============\n");
    printf("printing updated table\n");
    int numAtIdx;
    for (uint32_t i = 0; i < m_Size; ++i)
    {
        numAtIdx = *getArrayAt(i);
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    printf("==============\n");
}