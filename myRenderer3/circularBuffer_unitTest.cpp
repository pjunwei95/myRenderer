#include "circularBuffer.h"
#include "circularBuffer_unitTest.h"
#include "assert.h"
#include "logger.h"

void printCircBuf(CircularBuffer<int>* const cb) 
{
    uint32_t cbSize = cb->size();
    uint32_t tempFront = cb->frontIndex();
    logmsg("=========\n");
    for (uint32_t i = 0; i < cbSize; ++i)
    {
        uint32_t idx = (tempFront + i) % cb->capacity();
        //if (idx == cb->backIndex() && !cb->isFull())
            //break;
        //void* ptr = (uint8_t*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        //void* ptr = getArrayAt(&cb->m_Array, idx);
        int val = cb->at(idx);
        logmsg("%d ", val);
    }
    logmsg("\n=========\n");
}

void testPushPop()
{
    LOG_UNIT_TEST();
    CircularBuffer<int> cb(3);

    cb.isFull();
    for (int i = 0; i < 10; ++i)
    {
        if (cb.isFull())
            cb.popFront();
        cb.pushBack(i);
    }

    //print to console
    printCircBuf(&cb);

    logmsg("Popping...\n");
    cb.popFront();
    printCircBuf(&cb);

    logmsg("Popping...\n");
    cb.popFront();
    printCircBuf(&cb);

    logmsg("Pushing 99...\n");
    int rand = 99;
    cb.pushBack(rand);
    printCircBuf(&cb);
}

void testCircularBuffer()
{
    LOG_TEST(CIRCULAR BUFFER);
    testPushPop();
}
