#pragma once
#include <stdint.h>
#include <assert.h>
//#include "stdio.h"
#include "stdlib.h"

template<typename T>
class Array {
private:
    T* m_Data; // pointer to array
    uint32_t m_Size; // number of elements
    uint32_t m_Capacity; // available memory size

    //DEPRECATED
    //uint32_t m_TypeSize; // size of element type

    void checkMem();
public:
    Array() 
        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }
    {
    }

    explicit Array(uint32_t numElem) // new filled array of fixed size
        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ numElem } 
    {
        m_Data = static_cast<T*>(malloc(numElem * sizeof(T)));
    }

    ~Array()
    {
        if (m_Data)
            free(m_Data); 
    }

    uint32_t size() const 
    {
        return m_Size; 
    }
    uint32_t capacity() const
    {
        return m_Capacity; 
    }
    bool isEmpty() const
    {
        return 0 == m_Size; 
    }
    void popBack()
    {
        m_Size--; 
    }
    void addSize(uint32_t increment) 
    {
        m_Size += increment; 
    }

    T& operator[](uint32_t index)
    {
        return m_Data[index];
    }

    const T& operator[](uint32_t index) const
    {
        return m_Data[index];
    }

    Array& operator=(const Array& oldArray); //copy assignment, not move

    //TODO change T* to const T&
    T* front() const;
    T* back() const;
    T* at(const uint32_t index) const;
    void pushBack(const T* srcData);
    void insertAt(uint32_t index, const T* srcData);

    void eraseAt(uint32_t index);
    void clear();
    void removeAtFast(uint32_t index);

    //DEPRECATED
    //Array createNewArray(unsigned int sizeElem);
    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);
    //void* reallocArray(void* block, size_t oldSize, size_t newSize);
    //int getArrayTypeSize() const;
    //void freeArray();
    //void printTestArray();

};

//copy assignment, not move
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& oldArray)
{
    if (this == &oldArray)
        return *this;

    T* temp = static_cast<T*>(malloc(m_Capacity * sizeof(T)));
    uint32_t tempSize = oldArray.m_Size;
    uint32_t tempCap = oldArray.m_Capacity;

    for (uint32_t i = 0; i < tempCap; ++i)
        temp[i] = oldArray.m_Data[i];

    swap(tempSize, m_Size);
    swap(tempCap, m_Capacity);
    swap(temp, m_Data);

    free(temp);

    return *this;
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
void Array<T>::checkMem()
{
    if (!m_Data) // array memory uninitialised
    {
        m_Data = static_cast<T*>(malloc(sizeof(T)));
        assert(m_Data);
        m_Capacity++;
    }
    else if (m_Size == m_Capacity) // array memory exceeded
    {
        T* temp = static_cast<T*>(malloc(sizeof(T) * 2 * m_Capacity));
        for (uint32_t i = 0; i < m_Size; ++i)
            temp[i] = m_Data[i];
        free(m_Data);
        m_Data = temp;
        m_Capacity *= 2;
    }
}

template<typename T>
void Array<T>::pushBack(const T* srcData)
{
    assert(srcData);
    checkMem();
    assert(m_Size < m_Capacity);
    m_Data[m_Size] = *srcData;
    m_Size++;
}

template<typename T>
void Array<T>::insertAt(uint32_t index, const T* srcData)
{
    assert(srcData);
    assert(index < m_Size);

    checkMem();
    //shift array right
    // for i = size-1; i > index-1; i--
    for (int i = m_Size - 1; i > static_cast<int>(index) - 1; --i)
        m_Data[i + 1] = m_Data[i];
    m_Data[index] = *srcData;
    m_Size++;
}

template<typename T>
void Array<T>::eraseAt(uint32_t index)
{
    assert(!isEmpty());
    assert(index < m_Size);
    //shift array left
    // for i = index; i < size-1; i++
    //    A[i] = A[i+1]
    for (uint32_t i = index; i < m_Size; ++i)
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
