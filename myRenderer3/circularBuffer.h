#pragma once
#include "array.h"

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
    void printCircBuf() const;
    void pushFrontCircBuf(const T* srcData);
    void clearCircBuf();

public:
    CircularBuffer(uint32_t bufferLength);
    ~CircularBuffer();

    uint32_t getFrontIdxCircBuf() const;
    uint32_t getCapacityCircBuff() const;
    uint32_t getSizeCircBuf() const;
    T* popFrontCircBuf();
    T* getCircBufAt(uint32_t index) const;
    T* getFrontCircBuf() const;
    bool isFullCircBuf() const;
    void pushBackCircBuf(const T* srcData);

    //Deprecated
    //void freeCircBuf(CircularBuffer * const cb);
    //CircularBuffer createNewCircBuf(unsigned int bufferLength, unsigned int sizeElem);
};

