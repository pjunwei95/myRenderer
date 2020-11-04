#include "array_unitTest.h"
#include "logger.h"
#include "array.h"
//TODO 
//You should run suites of unit tests based off the commandline
//unit tests will meticulously test every functionality of  your Array / Circular buffer etc, with hardcoded inputs, and will compare them with hard coded expected values to ensure nothing breaks

void TestPrintArray(const Array<int>& vec, bool newline = true);

//Another printing method
//void printTestArray(const Array<int>* const a)
//{
//    logmsg("==============\n");
//    logmsg("printing updated table: \n\n");
//    int numAtIdx;
//    for (uint32_t i = 0; i < a->size(); ++i)
//    {
//        numAtIdx = a->at(i);
//        logmsg("array [%d] = %d\n", i, numAtIdx);
//    }
//    logmsg("==============\n");
//}

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
    TestPrintArray(a);

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
    TestPrintArray(a);

    //insert at idx
    int anotherNum = 333;
    logmsg("inserting a[%d] = %d...\n", 0, anotherNum);
    a.insertAt(0, anotherNum);
    logmsg("a[%d] is now = %d\n", 0, a.at(0));
    TestPrintArray(a);

    //remove at fast idx 5
    logmsg("RemoveAtFast 5...\n");
    a.removeAtFast(5);
    TestPrintArray(a);

    //remove last
    logmsg("popping last element...\n");
    a.popBack();

    //print last
    int getLast = a.back();
    logmsg("last = %d\n", getLast);
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
    TestPrintArray(container);
    logmsg("Size = %d\n", container.size());

    logmsg("Clear\n");
    container.clear();

    logmsg("After clear:\n");
    TestPrintArray(container);
    logmsg("Size = %d\n", container.size());
}

// This function prints all integral values contained in vector
void TestPrintArray(const Array<int>& vec, bool newline) {
    /*
    This for loop goes through the entire vector and prints out each element
    of the vector. Note the subscript usage on the my_vector class.
    */
    uint32_t size = vec.size();
    for (uint32_t i = 0; i < size; ++i) {
        logmsg("%i ", vec[i]);
    }

    // prints out the size and capacity of the vector
    uint32_t capacity = vec.capacity();
    logmsg("(size=%i, capacity=%i)", size, capacity);
    if (newline) {
        logmsg("\n");
    }
}

void TestPush() {
    logmsg("\n********** TestPush **********\n");
    Array<int> a;
    logmsg("Empty array:\n");
    TestPrintArray(a);

    // add 5 integers to the vector using push_back
    logmsg("push_back 5 integers:\n");
    for (int i = 0; i < 5; ++i) {
        a.pushBack(i);
        TestPrintArray(a);
    }

    // remove the last element of the vector as long as the vector is non-empty
    logmsg("pop_back until empty:\n");
    while (!a.isEmpty()) {
        a.popBack();
        TestPrintArray(a);
    }
}

void TestInsert() {
    logmsg("\n********** TestInsert **********\n");
    Array<int> a;
    logmsg("Empty array:\n");
    TestPrintArray(a);

    logmsg("push_back 5 integers:\n");
    for (int i = 0; i < 5; ++i) {
        a.pushBack(i);
        TestPrintArray(a);
    }

    // Insert value 99 in position 3
    logmsg("insert(3, 99):\n");
    a.insertAt(3, 99);
    TestPrintArray(a);

    // Insert value 98 in position 0
    logmsg("insert(0, 98):\n");
    a.insertAt(0, 98);
    TestPrintArray(a);

    // Insert value 97 in position 6
    logmsg("insert(6, 97):\n");
    a.insertAt(6, 97);
    TestPrintArray(a);
}


// First, notice that the Array object is created in a peculiar way.
// Second, notice that if the insert function were to insert in a position
// larger than the size of the current vector, it should abort the
// program.
void TestInsert1() {
    logmsg("\n********** TestInsert1 **********\n");
    int ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
    int size = sizeof(ia) / sizeof(*ia);
    logmsg("Construct from int array:\n");
    Array<int> org;

    for (int i = 0; i < size; ++i) {
        org.pushBack(ia[i]);
    }
    Array<int> a(org);
    TestPrintArray(a);

#if 0
    // Supposed to cause abort
    int index = a.size() * 2;
    logmsg("insert integer at index " << index << ":\n");
    a.insert(99, index);    // index too large, should cause abort
#else
    logmsg("Not tested really...change the macro in TestInsert1 to check\n");
#endif
}

void TestSubscripts() {
    logmsg("\n********** TestSubscripts **********\n");
    Array<int> a;

    logmsg("push_back 10 even integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
    }

    TestPrintArray(a);
    logmsg("multiple each value by 3:\n");
    for (int i = 0; i < 10; ++i) {
        a[i] = a[i] * 3;
    }
    TestPrintArray(a);
}

// Notice that the object is declared as read-only and
// also constructed in a peculiar way.
void TestSubscript1() {
    logmsg("\n********** TestSubscript1 **********\n");
    int ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
    int size = sizeof(ia) / sizeof(*ia);
    logmsg("Construct from int array:\n");
    Array<int> org;

    for (int i = 0; i < size; ++i) {
        org.pushBack(ia[i]);
    }
    Array<int> const a(org);
    TestPrintArray(a);

    int index = a.size() / 2;
    logmsg("using subscript: a[%i]\n", index);
    logmsg("a[%i] = %i\n", index, a[index]);
}

//#define TEST_SUBSCRIPT_2
// The purpose of this function is to inform the implementor that the
// subscript operator is supposed to cause an abort in the case when the
// given position is not within the bounds
void TestSubscript2() {
    logmsg("\n********** TestSubscript2 **********\n");
    int ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
    int size = sizeof(ia) / sizeof(*ia);
    logmsg("Construct from int array:\n");
    Array<int> org;

    for (int i = 0; i < size; ++i) {
        org.pushBack(ia[i]);
    }
    Array<int> const a(org);
    TestPrintArray(a);

#ifdef TEST_SUBSCRIPT_2
    //Supposed to cause abort
    int index = a.size() * 2;   // illegal
    logmsg("using subscript: a[%d]\n", index);
    logmsg("a[%d] = %d\n", index, a[index]);
#else
    logmsg("Not tested really...change the macro in TestSubscript2 to check\n");
#endif
}

void TestCopy() {
    logmsg("\n********** TestCopy **********\n");
    Array<int> a;

    logmsg("push_back 10 even integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
    }

    logmsg("Copy: b(a), print a,b\n");
    Array<int> b(a);
    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Copy: c(b), print b,c\n");
    const Array<int> c(b);
    TestPrintArray(b);
    TestPrintArray(c);
}

void TestAssign() 
{
    logmsg("\n********** TestAssign **********\n");
    Array<int> a, b;

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
    }

    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Assign: b = a, print a,b\n");
    b = a;
    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Assign: a = a, print a\n");
    a = a;
    TestPrintArray(a);
}

void TestErase() {
    logmsg("\n********** TestErase **********\n");
    Array<int> a;
    logmsg("Empty array:\n");
    TestPrintArray(a);

    logmsg("push_back 5 integers:\n");
    for (int i = 0; i < 5; ++i) {
        a.pushBack(i);
        TestPrintArray(a);
    }

    // Remove elements at position 0 and then position 3
    logmsg("erase(0), erase(3):\n");
    a.eraseAt(0);
    a.eraseAt(3);
    TestPrintArray(a);
}

void TestDeepCopy()
{
    logmsg("\n********** TestDeepCopy **********\n");
    Array<int> a, b;

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
    }

    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Assign: b = a, print a,b\n");
    b = a;
    TestPrintArray(a);
    TestPrintArray(b);

    int index = a.size() / 2;
    int changedValue = 99;
    logmsg("Modify a[%i] = %i, print a,b\n", index, changedValue);
    a[index] = changedValue;
    TestPrintArray(a);
    TestPrintArray(b);
}

void TestNestedArrayWithPointers() {
    logmsg("\n********** TestNestedArrayWithPointers **********\n");
    Array<int> a,b;

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
    }

    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Nested Array: Array<Array<int>>c, push a, b\n");
    Array<Array<int>*> c;
    c.pushBack(&a);
    c.pushBack(&b);

    logmsg("Obtain getA by accessing first element of C, print getA\n");
    Array<int>* getA = c[0];
    TestPrintArray(*getA);

    logmsg("Obtain getB by accessing second element of C, print getB\n");
    Array<int>* getB = c[1];
    TestPrintArray(*getB);
}

void TestNestedArray() {
    logmsg("\n********** TestNestedArray **********\n");
    Array<int> a, b;

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
    }

    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Nested Array: Array<Array<int>>c, push a, b\n");
    Array<Array<int>> c;
    c.pushBack(a);
    c.pushBack(b);

    logmsg("Obtain getA by accessing first element of C, print getA\n");
    Array<int> getA = c[0];
    TestPrintArray(getA);

    logmsg("Obtain getB by accessing second element of C, print getB\n");
    Array<int> getB = c[1];
    TestPrintArray(getB);
}

void testArray()
{
    LOG_TEST(ARRAY);

    TestPush();
    TestInsert();
    TestInsert1();
    TestCopy();
    TestAssign();
    TestErase();
    TestSubscripts();
    TestSubscript1();
    TestSubscript2();
    TestDeepCopy();
    TestNestedArrayWithPointers();
    //TestNestedArray();
    //testArray1();
    //testArray2();
    //testArrayClear();
}