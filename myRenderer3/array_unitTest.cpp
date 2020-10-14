#include "array.h"
#include "array_unitTest.h"
#include "logger.h"
//TODO 
//Separate all of your testing code into files like "Array_UnitTest.h/cpp"
//
//You should run suites of unit tests based off the commandline
//unit tests will meticulously test every functionality of  your Array / Circular buffer etc, with hardcoded inputs, and will compare them with hard coded expected values to ensure nothing breaks

#define LOG_TEST(name) logmsg("----------------------------------------------------TESTING "#name"\n");
#define LOG_UNIT_TEST() logmsg("---------------------------------In \"%s\"\n", __FUNCSIG__)


void printTestArray(const Array<int>* const a)
{
    logmsg("==============\n");
    logmsg("printing updated table: \n\n");
    int numAtIdx;
    for (uint32_t i = 0; i < a->size(); ++i)
    {
        numAtIdx = a->at(i);
        logmsg("array [%d] = %d\n", i, numAtIdx);
    }
    logmsg("==============\n");
}

void testArray1()
{
    LOG_UNIT_TEST();
    
    Array<int> a;
    int num = 0;
    //push 10 elements and print (init)
    for (int i = 0; i < 10; ++i)
    {
        a.pushBack(num);
        num++;
    }
    printTestArray(&a);

    //print first
    int getFirst = a.front();
    logmsg("first = %d\n", getFirst);

    //erase at idx
    logmsg("erasing a[%d] = %d...\n", 6, a.at(6));
    a.eraseAt(6);
    logmsg("a[%d] is now = %d\n", 6, a.at(6));

    //insert at idx
    int newNum = 99;
    logmsg("inserting a[%d] = %d...\n", 6, newNum);
    a.insertAt(6, newNum);
    logmsg("a[%d] is now = %d\n", 6, a.at(6));
    printTestArray(&a);

    //insert at idx
    int anotherNum = 333;
    logmsg("inserting a[%d] = %d...\n", 0, anotherNum);
    a.insertAt(0, anotherNum);
    logmsg("a[%d] is now = %d\n", 0, a.at(0));
    printTestArray(&a);

    //remove at fast idx 5
    logmsg("RemoveAtFast 5...\n");
    a.removeAtFast(5);
    printTestArray(&a);

    //remove last
    logmsg("popping last element...\n");
    a.popBack();

    //print last
    int getLast = a.back();
    logmsg("last = %d\n", getLast);

    //free after usage
    //delete a;
 }

void testArray2()
{
    LOG_UNIT_TEST();
    // for circular buffer, without this constructors will give linker errors
    Array<int> b;
    b.reserve(10);
    int num = 1;
    b.pushBack(num);
    num++;
    b.pushBack(num);
    num++;
    //b->addSize(1);
    b[0] = num;
    logmsg("capacity of b = %d\n", b.capacity());
    //int *num = b[0];
    //for profiler
}

void testArrayClear()
{
    LOG_UNIT_TEST();
    Array<int> container;
    container.pushBack(1);
    container.pushBack(2);
    container.pushBack(3);


    logmsg("Before clear:\n");
    printTestArray(&container);
    logmsg("Size = %d\n", container.size());

    logmsg("Clear\n");
    container.clear();

    logmsg("After clear:\n");
    printTestArray(&container);
    logmsg("Size = %d\n", container.size());
}

void testArray()
{
    LOG_TEST(ARRAY);
    testArray1();
    testArray2();
    testArrayClear();
}