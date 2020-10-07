#include "circularBuffer.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"

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
uint32_t CircularBuffer<T>::getCapacityCircBuff() const
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
        return (uint32_t) abs(m_Front - m_Back);
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

    m_Array.addArraySize(1);
    //memcpy(getBackCircBuf(cb), srcData, getArrayTypeSize(&cb->m_Array));
    T* back = getBackCircBuf();
    back = srcData;
    m_Back = (m_Back + 1) % m_Array.getArrayCapacity();
}

template<typename T>
void CircularBuffer<T>::pushFrontCircBuf(const T* srcData)
{
    assert(srcData);
    assert(!isFullCircBuf());

    m_Array.addArraySize(1);
    T* front = getFrontCircBuf();
    front = srcData;
    m_Front = (m_Front + 1) % m_Array.getArrayCapacity();
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
    return m_Array.getArrayAt(index);
}

void testCircularBuffer()
{
    //CircularBuffer* intCircBuf = createNewCircBuf(3, sizeof(int));
    CircularBuffer<int>* intCircBuf = new CircularBuffer<int>(3);


    for (int i = 0; i < 10; ++i)
    {
        if (intCircBuf->isFullCircBuf())
            intCircBuf->popFrontCircBuf();
        //pushBackCircBuf(&intCircBuf, &i);
    }

    ////print to console
    //printCircBuf(&intCircBuf);

    //logmsg("Popping...\n");
    //popFrontCircBuf(&intCircBuf);
    //printCircBuf(&intCircBuf);

    //logmsg("Popping...\n");
    //popFrontCircBuf(&intCircBuf);
    //printCircBuf(&intCircBuf);

    //logmsg("Pushing 99...\n");
    //int rand = 99;
    //pushBackCircBuf(&intCircBuf, &rand);
    //printCircBuf(&intCircBuf);

    //freeCircBuf(&intCircBuf);
}

template<typename T>
void CircularBuffer<T>::printCircBuf() const
{
    int tempFront = m_Front;
    logmsg("=========\n");
    for (int i = 0; i < m_Array.getArrayCapacity(); ++i)
    {
        int idx = (tempFront + i) % m_Array.getArrayCapacity();
        if (idx == m_Back && !isFullCircBuf())
            break;
        //void* ptr = (uint8_t*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        //void* ptr = getArrayAt(&cb->m_Array, idx);
        T* ptr = getCircBufAt(idx);
        logmsg("%d ", *((int*)ptr));
    }
    logmsg("\n==========\n");
}

