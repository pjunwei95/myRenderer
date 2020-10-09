#pragma once
#include "array.h"
#include <stdlib.h>
#include <string.h>


void testCircularBuffer();

template<typename T>
class CircularBuffer
{
private:
    Array<T>* m_Array;
    uint32_t m_Front;
    uint32_t m_Back;

    T* back() const;
    bool isEmpty() const;
    void clear();
    //void pushFrontCircBuf(const T* srcData);

public:
    //CircularBuffer(){}
    CircularBuffer(uint32_t bufferLength);
    ~CircularBuffer();

    uint32_t frontIndex() const;
    uint32_t backIndex() const;
    uint32_t capacity();
    uint32_t size() const;
    T* front() const;
    T* popFront();
    T* at(uint32_t index) const;
    bool isFull() const;
    void pushBack(const T* srcData);
    //void printCircBuf() const;


    //Deprecated
    //void freeCircBuf(CircularBuffer * const cb);
    //CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);
};

// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
template<typename T>
CircularBuffer<T>::CircularBuffer(uint32_t bufferLength)
    : m_Array{ nullptr }, m_Front{ 0 }, m_Back{ 0 }
{
    m_Array = new Array<T>(bufferLength);
    assert(m_Array);
}

template<typename T>
CircularBuffer<T>::~CircularBuffer()
{
    assert(m_Array);
    delete m_Array;
}

template<typename T>
uint32_t CircularBuffer<T>::frontIndex() const
{
    return m_Front;
}

template<typename T>
uint32_t CircularBuffer<T>::backIndex() const
{
    return m_Back;
}

template<typename T>
T* CircularBuffer<T>::front() const
{
    return &m_Array->at(m_Front);
}

template<typename T>
T* CircularBuffer<T>::back() const
{
    return m_Array->at(m_Back);
}

template<typename T>
uint32_t CircularBuffer<T>::capacity()
{
    return m_Array->capacity();
}

template<typename T>
uint32_t CircularBuffer<T>::size() const
{
    if (m_Front == m_Back)
    {
        if (m_Array->isEmpty())
            return 0;
        else
            return m_Array->capacity();
    }
    //difference in m_Front & m_Back
    else
        return (uint32_t)abs(m_Front - m_Back);
}

template<typename T>
bool CircularBuffer<T>::isFull() const
{
    return size() == m_Array->capacity();
}

template<typename T>
bool CircularBuffer<T>::isEmpty() const
{
    return m_Front == m_Back && !isFull();
}

//'push' a value directly into the 'back' slot
template<typename T>
void CircularBuffer<T>::pushBack(const T* srcData)
{
    assert(srcData);
    assert(!isFull());

    m_Array->addSize(1);
    memcpy(back(), srcData, sizeof(T));
    //m_Array->operator[](m_Back) = *srcData;
    m_Back = (m_Back + 1) % m_Array->capacity();
}

// When you 'pop', you simply move the 'front' cursor forward by one
template<typename T>
T* CircularBuffer<T>::popFront()
{
    assert(!isEmpty());
    T* ptrFront = m_Array->at(m_Front);
    m_Front = (m_Front + 1) % m_Array->capacity();

    return ptrFront;
}

template<typename T>
void CircularBuffer<T>::clear()
{
    assert(!isEmpty());
    m_Front = 0;
    m_Back = 0;
}

template<typename T>
T* CircularBuffer<T>::at(uint32_t index) const
{
    return m_Array->at(index);
}

