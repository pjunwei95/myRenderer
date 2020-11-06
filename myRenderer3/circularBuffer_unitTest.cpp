#include "circularBuffer.h"
#include "circularBuffer_unitTest.h"
#include "assert.h"
#include "logger.h"

namespace CircularBufferUnitTest {
    void printCircBuf(const CircularBuffer<int>& cb)
    {
        uint32_t size = cb.size();
        uint32_t back = cb.backIndex();

        uint32_t tempFront = cb.frontIndex();
        for (uint32_t i = 0; i < size; ++i)
        {
            uint32_t idx = (tempFront + i) % cb.capacity();
            int val = cb.at(idx);
            logmsg("%d ", val);
        }

        logmsg("[ ");
        for (uint32_t i = 0; i < size; ++i)
            logmsg("%d ", cb.at(i));
        logmsg("(size=%i, front=%i, back=%i)]\n", size, tempFront, back);
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

    void TestPushPop()
    {
        LOG_UNIT_TEST();
        CircularBuffer<int> cb(3);

        for (int i = 0; i < 5; ++i)
        {
            if (cb.isFull())
                cb.popFront();
            cb.pushBack(i);
        }

        printCircBuf(cb);

        logmsg("Popping...\n");
        cb.popFront();
        printCircBuf(cb);

    }

    void TestSpecialPush()
    {
        LOG_UNIT_TEST();
        logmsg("Test push 5 items\n");
        CircularBuffer<int> a(3);
        for (int i = 0; i < 5; ++i)
        {
            a.specialPushBack(i);
            logmsg("SpecialPushBack(%i) :\n", i);
            printCircBuf(a);
        }
    }

    void TestMultiplePushAndPop()
    {
        LOG_UNIT_TEST();
        CircularBuffer<int> a(3);
        for (int i = 0; i < 5; ++i)
            a.specialPushBack(i);
        printCircBuf(a);

        logmsg("\nBefore Pop Front:\n");
        printCircBuf(a);
        logmsg("After popping front = %i\n", a.popFront());
        printCircBuf(a);
        logmsg("\n");

        logmsg("\nBefore PushBack:\n");
        printCircBuf(a);
        logmsg("After PushBack 99:\n");
        a.pushBack(99);
        printCircBuf(a);

        logmsg("\nPopFront\nBefore: ");
        printCircBuf(a);
        logmsg("After popping front = %i\n", a.popFront());
        printCircBuf(a);
        logmsg("\n");

        logmsg("Special Push 123\n");
        a.specialPushBack(123);
        printCircBuf(a);

        logmsg("Special Push 321\n");
        a.specialPushBack(321);
        printCircBuf(a);
    }

    void TestCircularBufferStack()
    {
        LOG_UNIT_TEST();
        logmsg("creating stack a, b, c, d\n");
        Array<int> a, b, c, d;
        for (int i = 1; i < 10; ++i)
        {
            a.pushBack(i);
            b.pushBack(i * 2);
            c.pushBack(i * 3);
            d.pushBack(i * 4);
        }

        CircularBuffer<Array<int>> cb(3);
        cb.specialPushBack(a);
        logmsg("cb push a (size = %i, front = %i, back = %i)\n", cb.size(), cb.frontIndex(), cb.backIndex());
        cb.specialPushBack(b);
        logmsg("cb push b (size = %i, front = %i, back = %i)\n", cb.size(), cb.frontIndex(), cb.backIndex());
        cb.specialPushBack(c);
        logmsg("cb push c (size = %i, front = %i, back = %i)\n", cb.size(), cb.frontIndex(), cb.backIndex());
        cb.specialPushBack(d);
        logmsg("cb push d (size = %i, front = %i, back = %i)\n", cb.size(), cb.frontIndex(), cb.backIndex());

    }
}

void testCircularBuffer()
{
    LOG_TEST(CircularBuffer);
    logmsg("Buffer capacity: 3\n");
    CircularBufferUnitTest::TestPush();
    CircularBufferUnitTest::TestPushPop();
    CircularBufferUnitTest::TestSpecialPush();
    CircularBufferUnitTest::TestMultiplePushAndPop();
    CircularBufferUnitTest::TestCircularBufferStack();
}
