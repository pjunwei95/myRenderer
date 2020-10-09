#pragma once
#include <stdint.h>
#include <assert.h>
//#include "stdio.h"
#include "array.h"

// tests in array.cpp file
void testArray2();

template<typename T>
class Array {
private:
    T* m_Data; // pointer to array
    uint32_t m_Size; // number of elements
    uint32_t m_Capacity; // available memory size

    //DEPRECATED
    //uint32_t m_TypeSize; // size of element type

    void checkArraySuffMem();
public:
    Array();
    // new filled array of fixed size
    explicit Array(uint32_t numElem);
    ~Array();
    
    bool isEmpty() const;
    void addSize(int increment);
    uint32_t size() const;
    uint32_t capacity() const;
    T* front() const;
    T* back() const;
    T* at(const uint32_t index) const;
    void pushBack(const T* srcData);
    void popBack();
    void eraseAt(uint32_t index);
    void insertAt(uint32_t index, const T* srcData);
    void clear();
    void removeAtFast(uint32_t index);
    //void printTestArray();
    T& operator[](const uint32_t index);


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
}

template<typename T>
bool Array<T>::isEmpty() const
{
    assert(m_Data);
    return 0 == m_Size;
}

template<typename T>
uint32_t Array<T>::size() const
{
    assert(m_Data);
    return m_Size;
}

template<typename T>
void Array<T>::addSize(int increment)
{
    assert(m_Data);
    assert(increment);
    m_Size += increment;
}

template<typename T>
uint32_t Array<T>::capacity() const
{
    assert(m_Data);
    return m_Capacity;
}

template<typename T>
void Array<T>::clear()
{
    assert(m_Data);
    m_Size = 0;
}

template<typename T>
T* Array<T>::front() const
{
    assert(m_Data);
    return &m_Data[0];
}

template<typename T>
T* Array<T>::back() const
{
    assert(m_Data);
    return &m_Data[m_Size - 1];
}

template<typename T>
T* Array<T>::at(const uint32_t index) const
{
    assert(m_Data);
    assert(index < m_Size);
    return &m_Data[index];
}

template<typename T>
void Array<T>::popBack()
{
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
void Array<T>::pushBack(const T* srcData)
{
    assert(srcData);
    checkArraySuffMem();
    assert(m_Size < m_Capacity);
    m_Data[m_Size] = *srcData;
    m_Size++;
}

template<typename T>
void Array<T>::insertAt(uint32_t index, const T* srcData)
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
void Array<T>::eraseAt(uint32_t index)
{
    assert(!isEmpty());
    assert(index < m_Size);
    if (index == m_Size - 1) // last index
    {
        popBack(); //CHECK SIZE
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
void Array<T>::removeAtFast(uint32_t index)
{
    assert(!isEmpty());
    assert(index < m_Size);
    m_Data[index] = *back();
    m_Size--;
}

template<typename T>
T& Array<T>::operator[](const uint32_t index)
{
    assert(index < m_Size);
    return m_Data[index];
}

