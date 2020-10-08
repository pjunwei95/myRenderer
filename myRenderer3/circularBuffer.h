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

    T* getBackCircBuf() const;
    bool isCircBufEmpty() const;
    void clearCircBuf();
    //void pushFrontCircBuf(const T* srcData);

public:
    //CircularBuffer(){}
    CircularBuffer(uint32_t bufferLength);
    ~CircularBuffer();

    uint32_t getFrontIdxCircBuf() const;
    uint32_t getBackIdxCircBuf() const;
    uint32_t getCapacityCircBuff();
    uint32_t getSizeCircBuf() const;
    T* popFrontCircBuf();
    T* getCircBufAt(uint32_t index) const;
    T* getFrontCircBuf() const;
    bool isFullCircBuf() const;
    void pushBackCircBuf(const T* srcData);
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
uint32_t CircularBuffer<T>::getFrontIdxCircBuf() const
{
    return m_Front;
}

template<typename T>
uint32_t CircularBuffer<T>::getBackIdxCircBuf() const
{
    return m_Back;
}

template<typename T>
T* CircularBuffer<T>::getFrontCircBuf() const
{
    return &m_Array->getArrayAt(m_Front);
}

template<typename T>
T* CircularBuffer<T>::getBackCircBuf() const
{
    return m_Array->getArrayAt(m_Back);
}

template<typename T>
uint32_t CircularBuffer<T>::getCapacityCircBuff()
{
    return m_Array->getArrayCapacity();
}

template<typename T>
uint32_t CircularBuffer<T>::getSizeCircBuf() const
{
    if (m_Front == m_Back)
    {
        if (m_Array->isArrayEmpty())
            return 0;
        else
            return m_Array->getArrayCapacity();
    }
    //difference in m_Front & m_Back
    else
        return (uint32_t)abs(m_Front - m_Back);
}

template<typename T>
bool CircularBuffer<T>::isFullCircBuf() const
{
    return getSizeCircBuf() == m_Array->getArrayCapacity();
}

template<typename T>
bool CircularBuffer<T>::isCircBufEmpty() const
{
    return m_Front == m_Back && !isFullCircBuf();
}

//'push' a value directly into the 'back' slot
template<typename T>
void CircularBuffer<T>::pushBackCircBuf(const T* srcData)
{
    assert(srcData);
    assert(!isFullCircBuf());

    m_Array->addArraySize(1);
    memcpy(getBackCircBuf(), srcData, sizeof(T));
    //m_Array->operator[](m_Back) = *srcData;
    m_Back = (m_Back + 1) % m_Array->getArrayCapacity();
}

// When you 'pop', you simply move the 'front' cursor forward by one
template<typename T>
T* CircularBuffer<T>::popFrontCircBuf()
{
    assert(!isCircBufEmpty());
    T* ptrFront = m_Array->getArrayAt(m_Front);
    m_Front = (m_Front + 1) % m_Array->getArrayCapacity();

    return ptrFront;
}

template<typename T>
void CircularBuffer<T>::clearCircBuf()
{
    assert(!isCircBufEmpty());
    m_Front = 0;
    m_Back = 0;
}

template<typename T>
T* CircularBuffer<T>::getCircBufAt(uint32_t index) const
{
    return m_Array->getArrayAt(index);
}

