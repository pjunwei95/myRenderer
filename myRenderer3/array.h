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

    void checkMem();
    T* realloc(size_t newSize);

    //DEPRECATED
    //uint32_t m_TypeSize; // size of element type

public:
    Array() 
        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }
    {
    }
    ~Array()
    {
        for (uint32_t i = 0; i < m_Capacity; ++i)
            m_Data[i].~T();

        free(m_Data); 
    }

    T& operator[](uint32_t index)
    {
        return m_Data[index];
    }

    const T& operator[](uint32_t index) const
    {
        return m_Data[index];
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
        T& ref = back();
        ref.~T();
        m_Size--;
    }
    void incrementSize(uint32_t value) 
    {
        m_Size += value; 
    }
    void decrementSize(uint32_t value)
    {
        m_Size -= value;
    }

    const T& front() const
    {
        assert(m_Data);
        return m_Data[0];
    }
    const T& back() const
    {
        assert(m_Data);
        return m_Data[m_Size - 1];
    }
    const T& at(const uint32_t index) const
    {
        assert(m_Data);
        assert(index < m_Size);
        return m_Data[index];
    }
    T& front()
    {
        assert(m_Data);
        return m_Data[0];
    }
    T& back()
    {
        assert(m_Data);
        return m_Data[m_Size - 1];
    }
    T& at(const uint32_t index)
    {
        assert(m_Data);
        assert(index < m_Size);
        return m_Data[index];
    }

    Array& operator=(const Array& oldArray); //copy assignment, not move
    void pushBack(const T& srcData);
    void insertAt(uint32_t index, const T& srcData);
    void reserve(uint32_t numElem);
    void eraseAt(uint32_t index);
    void removeAtFast(uint32_t index);
    void clear();
    void insertAtFast(uint32_t index, const T& srcData);

    //DEPRECATED
    //Array createNewArray(unsigned int sizeElem);
    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);
    //int getArrayTypeSize() const;
    //void freeArray();
    //void printTestArray();

};

template<typename T>
T* Array<T>::realloc(size_t newSize)
{
    T* temp = static_cast<T*>(malloc(sizeof(T) * newSize));
    if (temp)
    {
        for (uint32_t i = 0; i < m_Size; ++i)
            temp[i] = m_Data[i];
        free(m_Data);
        return temp;
    }
    else // failed to allocate memory
        return m_Data;
}

template<typename T>
void Array<T>::reserve(uint32_t newCap) // new filled array of fixed size
{
    if (newCap <= m_Capacity)
        return;

    if (m_Data)
    {
        T* temp = realloc(newCap);
        assert(temp);
        m_Data = temp;
    }
    else
    {
        m_Data = static_cast<T*>(malloc(newCap * sizeof(T)));
        assert(m_Data);
    }
    m_Capacity = newCap;
}

//copy assignment, not move
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhsArray)
{
    if (this == &rhsArray)
        return *this;

    T* temp = realloc(m_Capacity);
    assert(temp);
    m_Data = temp;

    return *this;
}

template<typename T>
void Array<T>::clear()
{
    assert(m_Data);
    for (uint32_t i = 0; i < m_Size; ++i)
        m_Data[i].~T();
    m_Size = 0;
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
        m_Capacity *= 2;
        T* temp = realloc(m_Capacity);
        assert(temp);
        m_Data = temp;
    }
}

template<typename T>
void Array<T>::pushBack(const T& srcData)
{
    checkMem();
    assert(m_Size < m_Capacity);
    m_Data[m_Size] = srcData;
    m_Size++;
}

template<typename T>
void Array<T>::insertAt(uint32_t index, const T& srcData)
{
    assert(index <= m_Size);
    checkMem();
    //shift array right
    // for i = size-1; i > index-1; i--
    for (int i = m_Size - 1; i > static_cast<int>(index) - 1; --i)
        m_Data[i + 1] = m_Data[i];
    m_Data[index] = srcData;
    m_Size++;
}

template<typename T>
void Array<T>::eraseAt(uint32_t index)
{
    //shift array left
    assert(!isEmpty());
    assert(index < m_Size);
    // for i = index; i < size-1; i++
    for (uint32_t i = index; i < m_Size; ++i)
        m_Data[i] = m_Data[i + 1]; //A[i] = A[i+1]
    m_Data[m_Size].~T();
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
    m_Data[index] = back();
    popBack();
}

template<typename T>
void Array<T>::insertAtFast(uint32_t index, const T& srcData) 
{
    assert(!isEmpty());
    assert(index <= m_Size);
    const T& temp = m_Data[index];
    pushBack(temp);
    m_Data[index] = srcData;
}
