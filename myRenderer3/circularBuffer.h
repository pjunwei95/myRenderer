#pragma once
#include "array.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"

template<typename T>
class CircularBuffer
{
private:
    Array<T> m_Array;
    uint32_t m_Front;
    uint32_t m_Back;

    void clear();

    //const T& back() { return m_Array->at(m_Back); }
    //void pushFrontCircBuf(const T* srcData);

public:
    // A circular buffer is simply an array but with 2 cursors, front & back
    // the cursors are simply index values
    CircularBuffer(uint32_t bufferLength)
        : m_Front{ 0 }, m_Back{ 0 }
    {
        m_Array.reserve(bufferLength); // reserve one slot to avoid reallocation
    }

    ~CircularBuffer(){}

    uint32_t frontIndex() const { return m_Front; }
    uint32_t backIndex() const { return m_Back; }
    uint32_t capacity() const { return m_Array.capacity(); }
    const T& front() { return m_Array.at(m_Front); }
    const T& at(uint32_t index) const 
    {
        return m_Array[index]; 
        //return m_Array.at(index); 
        //this will check bounds hereby carrying eroor
        //      index 0 1 2
        //e.g. actual 3 4 99
        //displayed   # 4 99
        //where # is garbage, because size = 2
    }
    bool isEmpty() const { return 0 == size(); }
    bool isFull() const { return size() == m_Array.capacity(); }

    const T& popFront();
    //pushback increases back index
    void pushBack(const T& srcData);
    uint32_t size() const;
    void specialPushBack(const T& srcData);


    //DEPRECATED
    //void freeCircBuf(CircularBuffer * const cb);
    //CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);
};

template<typename T>
void CircularBuffer<T>::specialPushBack(const T& srcData)
{
    if (isFull())
        popFront();
    pushBack(srcData);
}

template<typename T>
uint32_t CircularBuffer<T>::size() const
{
    //return m_Array.size();
    if (m_Front == m_Back) // can be full or empty
    {
        if (0 == m_Array.size())
            return 0;
        else
            return m_Array.capacity();
    }
    else if (m_Back > m_Front) //expected, back greater than front
    {
        return m_Back - m_Front;
    }
    else // front greater than back
        return m_Array.capacity() + m_Back - m_Front;
}

//'push' a value directly into the 'back' slot
template<typename T>
void CircularBuffer<T>::pushBack(const T& srcData)
{
    assert(!isFull());
    m_Array[m_Back] = srcData;
    m_Array.incrementSize(1);
    m_Back = (m_Back + 1) % m_Array.capacity();
}

// When you 'pop', you simply move the 'front' cursor forward by one
template<typename T>
const T& CircularBuffer<T>::popFront()
{
    assert(!isEmpty());
    const T& ref = m_Array[m_Front];
    m_Array.decrementSize(1);
    m_Front = (m_Front + 1) % m_Array.capacity();
    return ref;
}

template<typename T>
void CircularBuffer<T>::clear()
{
    assert(m_Array);
    m_Array.clear();
    m_Front = 0;
    m_Back = 0;
}

