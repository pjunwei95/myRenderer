//#include "circularBuffer.h"
//#include "assert.h"
//#include "logger.h"
//
//void printCircBuf(CircularBuffer<int>* const cb) 
//{
//    int tempFront = cb->frontIndex();
//    logmsg("=========\n");
//    for (uint32_t i = 0; i < cb->capacity(); ++i)
//    {
//        uint32_t idx = (tempFront + i) % cb->capacity();
//        if (idx == cb->backIndex() && !cb->isFull())
//            break;
//        //void* ptr = (uint8_t*)cb->m_Array.m_Data + (idx * cb->m_Array.m_TypeSize);
//        //void* ptr = getArrayAt(&cb->m_Array, idx);
//        int* ptr = cb->at(idx);
//        logmsg("%d ", *((int*)ptr));
//    }
//    logmsg("\n==========\n");
//}
//
//void testCircularBuffer()
//{
//    CircularBuffer<int>* intCircBuf = new CircularBuffer<int>(3);
//
//    intCircBuf->isFull();
//    for (int i = 0; i < 10; ++i)
//    {
//        if (intCircBuf->isFull())
//            intCircBuf->popFront();
//        intCircBuf->pushBack(&i);
//    }
//
//    //print to console
//    printCircBuf(intCircBuf);
//
//    logmsg("Popping...\n");
//    intCircBuf->popFront();
//    printCircBuf(intCircBuf);
//
//    logmsg("Popping...\n");
//    intCircBuf->popFront();
//    printCircBuf(intCircBuf);
//
//    logmsg("Pushing 99...\n");
//    int rand = 99;
//    intCircBuf->pushBack(&rand);
//    printCircBuf(intCircBuf);
//
//    delete intCircBuf;
//}
