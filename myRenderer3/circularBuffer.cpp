#include "circularBuffer.h"
#include "assert.h"
#include "logger.h"

void printCircBuf(CircularBuffer<int>* const cb) 
{
    int tempFront = cb->getFrontIdxCircBuf();
    logmsg("=========\n");
    for (uint32_t i = 0; i < cb->getCapacityCircBuff(); ++i)
    {
        uint32_t idx = (tempFront + i) % cb->getCapacityCircBuff();
        if (idx == cb->getBackIdxCircBuf() && !cb->isFullCircBuf())
            break;
        //void* ptr = (uint8_t*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
        //void* ptr = getArrayAt(&cb->m_Array, idx);
        int* ptr = cb->getCircBufAt(idx);
        logmsg("%d ", *((int*)ptr));
    }
    logmsg("\n==========\n");
}

void testCircularBuffer()
{
    CircularBuffer<int>* intCircBuf = new CircularBuffer<int>(3);

    intCircBuf->isFullCircBuf();
    for (int i = 0; i < 10; ++i)
    {
        if (intCircBuf->isFullCircBuf())
            intCircBuf->popFrontCircBuf();
        intCircBuf->pushBackCircBuf(&i);
    }

    //print to console
    printCircBuf(intCircBuf);

    logmsg("Popping...\n");
    intCircBuf->popFrontCircBuf();
    printCircBuf(intCircBuf);

    logmsg("Popping...\n");
    intCircBuf->popFrontCircBuf();
    printCircBuf(intCircBuf);

    logmsg("Pushing 99...\n");
    int rand = 99;
    intCircBuf->pushBackCircBuf(&rand);
    printCircBuf(intCircBuf);

    delete intCircBuf;
}
