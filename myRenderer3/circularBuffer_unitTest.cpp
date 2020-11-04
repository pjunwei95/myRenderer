#include "circularBuffer.h"
#include "circularBuffer_unitTest.h"
#include "assert.h"
#include "logger.h"

namespace CircularBufferUnitTest {
    void printCircBuf(const CircularBuffer<int>& cb)
    {
        uint32_t cbSize = cb.size();
        uint32_t tempFront = cb.frontIndex();
        logmsg("=========\n");
        for (uint32_t i = 0; i < cbSize; ++i)
        {
            uint32_t idx = (tempFront + i) % cb.capacity();
            int val = cb.at(idx);
            logmsg("%d ", val);
        }
        logmsg("\n=========\n");
    }

    void testPushPop()
    {
        LOG_UNIT_TEST();
        CircularBuffer<int> cb(3);

        cb.isFull();
        for (int i = 0; i < 5; ++i)
        {
            if (cb.isFull())
                cb.popFront();
            cb.pushBack(i);
        }

        //print to console
        printCircBuf(cb);

        logmsg("Popping...\n");
        cb.popFront();
        printCircBuf(cb);

    }

    void TestPush()
    {
        LOG_UNIT_TEST();
        logmsg("Test push 3 items\n");
        CircularBuffer<int> a(3);
        for (int i = 0; i < 3; ++i)
            a.pushBack(i);
        printCircBuf(a);
    }

    void TestPop()
    {
        LOG_UNIT_TEST();
        CircularBuffer<int> a(3);
        for (int i = 0; i < 3; ++i)
            a.pushBack(i);
        printCircBuf(a);
        int popped = a.popFront();
        logmsg("popped = %i\n", popped);
    }

    void TestSpecialPush()
    {
        LOG_UNIT_TEST();
        logmsg("Test push 5 items\n");
        CircularBuffer<int> a(3);
        for (int i = 0; i < 5; ++i)
            a.specialPushBack(i);
        printCircBuf(a);
    }

}

void testCircularBuffer()
{
    LOG_TEST(CIRCULAR BUFFER);
    logmsg("Buffer size: 3\n");
    //testPushPop();
    CircularBufferUnitTest::TestPush();
    CircularBufferUnitTest::TestPop();
    CircularBufferUnitTest::TestSpecialPush();
}
