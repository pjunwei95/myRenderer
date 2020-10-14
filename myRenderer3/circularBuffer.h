#pragma once
#include "array.h"
#include <stdlib.h>
#include <string.h>

void testCircularBuffer();

//pushback increases back index
template<typename T>
class CircularBuffer
{
private:
    Array<T> m_Array;
    uint32_t m_Capacity;
    uint32_t m_Front;
    uint32_t m_Back;

    T& back() { return m_Array->at(m_Back); }
    void clear();

    //DEPRECATED
    //void pushFrontCircBuf(const T* srcData);

public:
    CircularBuffer(uint32_t bufferLength);
    ~CircularBuffer();

    T& popFront();
    void pushBack(const T& srcData);
    uint32_t size() const;

    uint32_t frontIndex() const { return m_Front; }
    uint32_t backIndex() const { return m_Back; }
    uint32_t capacity() { return m_Capacity; }
    T& front() { return m_Array.at(m_Front); }
    T& at(uint32_t index) { return m_Array.at(index); }

    bool isEmpty() const
    {
        return 0 == size();
    }
    bool isFull() const
    {
        return size() == m_Capacity;
    }

    

    //DEPRECATED
    //void freeCircBuf(CircularBuffer * const cb);
    //CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);
};



// A circular buffer is simply an array but with 2 cursors, front & back
// the cursors are simply index values
template<typename T>
CircularBuffer<T>::CircularBuffer(uint32_t bufferLength)
    : m_Front{ 0 }, m_Back{ 0 }, m_Capacity {bufferLength}
{
    m_Array.reserve(bufferLength + 1); // reserve one slot to avoid reallocation
}

template<typename T>
CircularBuffer<T>::~CircularBuffer()
{
    //~Array<T>();
}

template<typename T>
uint32_t CircularBuffer<T>::size() const
{
    if (m_Front == m_Back) // can be full or empty
    {
        if (0 == m_Array.size())
            return 0;
        else
            return m_Capacity;
    }
    else if (m_Back > m_Front) //expected, back greater than front
    {
        return m_Back - m_Front + 1;
    }
    else // front greater than back
        return m_Capacity + m_Back + 1 - m_Front;
}

//'push' a value directly into the 'back' slot
template<typename T>
void CircularBuffer<T>::pushBack(const T& srcData)
{
    assert(!isFull());
    m_Array.pushBack(srcData);
    m_Back = (m_Back + 1) % m_Capacity;
}

// When you 'pop', you simply move the 'front' cursor forward by one
template<typename T>
T& CircularBuffer<T>::popFront()
{
    assert(!isEmpty());
    T& ptrFront = m_Array.at(m_Front);
    m_Front = (m_Front + 1) % m_Capacity;

    return ptrFront;
}

template<typename T>
void CircularBuffer<T>::clear()
{
    assert(!isEmpty());
    m_Front = 0;
    m_Back = 0;
}

