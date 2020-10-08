#include "stdio.h"
#include "array.h"

void printTestArray(const Array<int>* const a)
{
    printf("==============\n");
    printf("printing updated table\n");
    int numAtIdx;
    for (uint32_t i = 0; i < a->getArraySize(); ++i)
    {
        numAtIdx = *a->getArrayAt(i);
        printf("array [%d] = %d\n", i, numAtIdx);
    }
    printf("==============\n");
}

void testArray2()
{
    Array<int>* a = new Array<int>();
    int num = 0;
    //push 10 elements and print (init)
    for (int i = 0; i < 10; ++i)
    {
        a->pushBackArray(&num);
        num++;
    }
    printTestArray(a);

    //print first
    int getFirst = *a->getArrayFront();
    printf("first = %d\n", getFirst);

    //erase at idx
    printf("erasing a[%d] = %d...\n", 6, *a->getArrayAt(6));
    a->eraseArrayAt(6);
    printf("a[%d] is now = %d\n", 6, *a->getArrayAt(6));

    //insert at idx
    int newNum = 99;
    printf("inserting a[%d] = %d...\n", 6, newNum);
    a->insertArray(6, &newNum);
    printf("a[%d] is now = %d\n", 6, *a->getArrayAt(6));
    printTestArray(a);

    //remove at fast idx 5
    printf("RemoveAtFast 5...\n");
    a->removeAtFastArray(5);
    printTestArray(a);

    //remove last
    printf("popping last element...\n");
    a->popBackArray();

    //print last
    int getLast = *a->getArrayBack();
    printf("last = %d\n", getLast);

    //free after usage
    delete a;
}


void testB()
{
    // for circular buffer, without this constructors will give linker errors
    Array<int>* b = new Array<int>(3);
    b->getArrayCapacity();
    b->addArraySize(1);
    int num = 9;
    b->operator[](0) = num;

    //for profiler
}
