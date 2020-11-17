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

void TestArrayCombined()
{
    LOG_UNIT_TEST();
    
    Array<int> a;
    int num = 0;
    //push 10 elements and print (init)
    for (int i = 0; i < 10; ++i)
    {
        a.pushBack(num);
        assert(a[i] == num);
        num++;
    }
    TestPrintArray(a);
    assert(a.size() == 10);

    //print first
    int getFirst = a.front();
    logmsg("first = %d\n", getFirst);
    assert(a.front() == 0);

    //erase at idx
    logmsg("erasing a[%d] = %d...\n", 6, a.at(6));
    a.eraseAt(6);
    logmsg("a[%d] is now = %d\n", 6, a.at(6));
    assert(a[6] == 7);
    assert(a.size() == 9);

    //insert at idx
    int newNum = 99;
    logmsg("inserting a[%d] = %d...\n", 6, newNum);
    a.insertAt(6, newNum);
    logmsg("a[%d] is now = %d\n", 6, a.at(6));
    TestPrintArray(a);
    assert(a[6] == 99);
    assert(a[7] == 7);
    assert(a.size() == 10);

    //insert at idx
    int anotherNum = 333;
    logmsg("inserting a[%d] = %d...\n", 0, anotherNum);
    a.insertAt(0, anotherNum);
    logmsg("a[%d] is now = %d\n", 0, a.at(0));
    TestPrintArray(a);
    assert(a[0] == 333);
    assert(a[1] == 0);
    assert(a.size() == 11);

    //remove at fast idx 5
    logmsg("RemoveAtFast 5...\n");
    a.removeAtFast(5);
    TestPrintArray(a);
    assert(a[5] == 9);
    assert(a.back() == 8);
    assert(a.size() == 10);

    //remove last
    logmsg("popping last element...\n");
    a.popBack();
    assert(a.size() == 9);

    //print last
    int getLast = a.back();
    logmsg("last = %d\n", getLast);
    assert(a.back() == 7);
    assert(a.capacity() == 16);
}

void TestReserve()
{
    LOG_UNIT_TEST();
    Array<int> a;
    a.reserve(10);
    assert(a.capacity() == 10);
    assert(a.size() == 0);
    a.reserve(5);
    assert(a.capacity() == 10);
    a.reserve(20);
    assert(a.capacity() == 20);
}

void TestClear()
{
    LOG_UNIT_TEST();
    Array<int> container;
    container.pushBack(1);
    container.pushBack(2);
    container.pushBack(3);

    logmsg("Before clear:\n");
    TestPrintArray(container);
    logmsg("Size = %d\n", container.size());
    assert(container.size() == 3);

    logmsg("Clear\n");
    container.clear();

    logmsg("After clear:\n");
    TestPrintArray(container);
    logmsg("Size = %d\n", container.size());
    assert(container.size() == 0);
}

// This function prints all integral values contained in vector
void TestPrintArray(const Array<int>& vec, bool newline) {
    /*
    This for loop goes through the entire vector and prints out each element
    of the vector. Note the subscript usage on the array class.
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

    for (int i = 0; i < 5; ++i)
        assert(a[i] == i);

    assert(a.size() == 5);
    assert(a.capacity() == 8);
}

void TestPushPop()
{
    logmsg("\n********** TestPushPop **********\n");
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

    assert(a.size() == 0);
    assert(a.capacity() == 8);
}

void TestStressPush() {
    logmsg("\n********** TestStressPush **********\n");
    Array<int> a;
    for (int i = 0; i < 1000; ++i) 
        a.pushBack(i);

    for (int i = 0; i < 1000; ++i)
        assert(a[i] == i);

    assert(a.size() == 1000);
    assert(a.capacity() == 1024);
}

void TestInsert() {
    logmsg("\n********** TestInsert **********\n");
    Array<int> a;
    int ans1[] = { 0, 1, 2, 3, 4 };
    logmsg("Empty array:\n");
    TestPrintArray(a);

    logmsg("push_back 5 integers:\n");
    for (int i = 0; i < 5; ++i) {
        a.pushBack(i);
        TestPrintArray(a);
        assert(a[i] == ans1[i]);
    }
    assert(a.capacity() == 8);


    // Insert value 99 in position 3
    logmsg("insert(3, 99):\n");
    a.insertAt(3, 99);
    TestPrintArray(a);
    assert(a.size() == 6);

    // Insert value 98 in position 0
    logmsg("insert(0, 98):\n");
    a.insertAt(0, 98);
    TestPrintArray(a);
    assert(a.size() == 7);

    // Insert value 97 in position 6
    logmsg("insert(6, 97):\n");
    a.insertAt(6, 97);
    TestPrintArray(a);
    assert(a.size() == 8);

    int ans2[] = { 98, 0, 1, 2, 99, 3, 97, 4 };
    for (int i = 0; i < 5; ++i) 
        assert(a[i] == ans2[i]);
    assert(a.capacity() == 8);
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
    logmsg("insert integer at index %i:\n", index);
    a.insertAt(index, 99);    // index too large, should cause abort
#else
    logmsg("Not tested really...change the macro in TestInsert1 to check\n");
#endif
}

void TestSubscripts() {
    logmsg("\n********** TestSubscripts **********\n");
    Array<int> a;
    int ia[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };


    logmsg("push_back 10 even integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        assert(a[i] == ia[i]);
    }
    TestPrintArray(a);

    int ia2[] = { 0, 6, 12, 18, 24, 30, 36, 42, 48, 54 };
    logmsg("multiple each value by 3:\n");
    for (int i = 0; i < 10; ++i) {
        a[i] = a[i] * 3;
        assert(a[i] == ia2[i]);
    }
    TestPrintArray(a);
}

// Notice that the object is declared as read-only and
// also constructed in a peculiar way.
void TestAt1() {
    logmsg("\n********** TestAt1 **********\n");
    int ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
    int size = sizeof(ia) / sizeof(*ia);
    logmsg("Construct from int array:\n");
    Array<int> org;

    for (int i = 0; i < size; ++i) 
    {
        org.pushBack(ia[i]);
        assert(org.at(i) == ia[i]);
    }
    Array<int> const a(org);
    TestPrintArray(a);

    int index = a.size() / 2;
    logmsg("using subscript: a[%i]\n", index);
    logmsg("a[%i] = %i\n", index, a[index]);
    assert(a[index] == ia[index]);
}

//#define TEST_AT_2
// The purpose of this function is to inform the implementor that the
// subscript operator is supposed to cause an abort in the case when the
// given position is not within the bounds
void TestAt2() {
    logmsg("\n********** TestAt2 **********\n");
    int ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
    int size = sizeof(ia) / sizeof(*ia);
    logmsg("Construct from int array:\n");
    Array<int> org;

    for (int i = 0; i < size; ++i) {
        org.pushBack(ia[i]);
        assert(org.at(i) == ia[i]);
}
    Array<int> const a(org);
    TestPrintArray(a);

#ifdef TEST_AT_2
    //Supposed to cause abort
    int index = a.size() * 2;   // illegal
    logmsg("using at: a.at(%d)\n", index);
    logmsg("a.at(%d) = %d\n", index, a.at(index));
#else
    logmsg("Not tested really...change the macro in TestAt2 to check\n");
#endif
}

void TestCopy() {
    logmsg("\n********** TestCopy **********\n");
    Array<int> a;
    int ans[10] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

    logmsg("push_back 10 even integers:\n");
    for (int i = 0; i < 10; ++i)
        a.pushBack(2 * i);

    logmsg("Copy: b(a), print a,b\n");
    Array<int> b(a);
    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Copy: c(b), print b,c\n");
    const Array<int> c(b);
    TestPrintArray(b);
    TestPrintArray(c);

    for (int i = 0; i < 10; ++i)
    {
        assert(a[i] == ans[i]);
        assert(b[i] == ans[i]);
        assert(c[i] == ans[i]);
    }

}

void TestAssign() 
{
    logmsg("\n********** TestAssign **********\n");
    Array<int> a, b;
    int ans1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ans2[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
        assert(a[i] == ans2[i]);
        assert(b[i] == ans1[i]);
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

    for (int i = 0; i < 10; ++i)
    {
        assert(a[i] == ans2[i]);
        assert(b[i] == ans2[i]);
    }

}

void TestErase() {
    logmsg("\n********** TestErase **********\n");
    Array<int> a;
    int ans1[] = { 0, 1, 2, 3, 4 };
    logmsg("Empty array:\n");
    TestPrintArray(a);

    logmsg("push_back 5 integers:\n");
    for (int i = 0; i < 5; ++i) {
        a.pushBack(i);
        assert(a[i] == ans1[i]);
        TestPrintArray(a);
    }

    // Remove elements at position 0 and then position 3
    logmsg("erase(0), erase(3):\n");
    a.eraseAt(0);
    a.eraseAt(3);
    TestPrintArray(a);
    int ans2[] = { 1, 2, 3 };
    assert(a.size() == 3);
    for (int i = 0; i < 3; ++i)
        assert(a[i] == ans2[i]);

}

void TestDeepCopy()
{
    logmsg("\n********** TestDeepCopy **********\n");
    Array<int> a, b;
    int ans1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ans2[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) 
    {
        a.pushBack(2 * i);
        b.pushBack(i);
        assert(a[i] == ans2[i]);
        assert(b[i] == ans1[i]);
    }

    TestPrintArray(a);
    TestPrintArray(b);

    logmsg("Assign: b = a, print a,b\n");
    b = a;
    TestPrintArray(a);
    TestPrintArray(b);
    for (int i = 0; i < 10; ++i)
        assert(b[i] == ans2[i]);

    int index = a.size() / 2;
    int changedValue = 99;
    int ans3[] = { 0, 2, 4, 6, 8, changedValue, 12, 14, 16, 18 };
    logmsg("Modify a[%i] = %i, print a,b\n", index, changedValue);
    a[index] = changedValue;
    TestPrintArray(a);
    TestPrintArray(b);
    assert(a[index] == ans3[index]);
    assert(b[index] == ans2[index]);
}

void TestNestedArrayWithPointers() {
    logmsg("\n********** TestNestedArrayWithPointers **********\n");
    Array<int> a,b;
    int ans1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ans2[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

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
    Array<int> a, b, c;
    int ans1[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
    int ans2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ans3[] = { 0, 3, 6, 9, 12, 15, 18, 21, 24, 27 };


    logmsg("push_back 10 integers:\n");
    for (int i = 0; i < 10; ++i) {
        a.pushBack(2 * i);
        b.pushBack(i);
        c.pushBack(3 * i);
    }

    TestPrintArray(a);
    TestPrintArray(b);
    TestPrintArray(c);

    logmsg("Nested Array: Array<Array<int>>c, push a, b, c\n");
    Array<Array<int>> d;
    d.pushBack(a);
    d.pushBack(b);
    d.pushBack(c);

    logmsg("Obtain getA by accessing first element of D, print getA\n");
    Array<int> getA = d[0];
    TestPrintArray(getA);

    logmsg("Obtain getB by accessing second element of D, print getB\n");
    Array<int> getB = d[1];
    TestPrintArray(getB);

    logmsg("Obtain getC by accessing third element of D, print getC\n");
    Array<int> getC = d[2];
    TestPrintArray(getC);

    for (int i = 0; i < 10; ++i)
    {
        assert(getA[i] == ans1[i]);
        assert(getB[i] == ans2[i]);
        assert(getC[i] == ans3[i]);
    }
}

void TestConstructor()
{
    LOG_UNIT_TEST();
    Array<int> a;
    assert(a.size() == 0);
    assert(a.capacity() == 0);
}

void TestOtherDataType()
{
    LOG_UNIT_TEST();
    Array<float> f;
    Array<double> d;
    float floatRes[] = { 1.1f, 2.2f, 3.3f };
    double doubleRes[] = { 1.1, 2.2, 3.3 };

    for (float i = 1.0f; i <= 3; ++i)
    {
        f.pushBack(i + i / 10.0f);
    }

    for (double i = 1.0; i <= 3; ++i)
    {
        d.pushBack(i + i / 10.0);
    }

    assert(sizeof(f) == sizeof(d));
    for (int i = 0; i < 3; ++i)
    {
        assert(f[i] == floatRes[i]);
        assert(d[i] == doubleRes[i]);
    }


}


void TestArray()
{
    LOG_TEST(ARRAY);
    TestConstructor();
    TestPush();
    TestStressPush();
    TestPushPop();
    TestCopy();
    TestAssign();
    TestDeepCopy();
    TestSubscripts();
    TestAt1();
    TestAt2();
    TestInsert();
    TestInsert1();
    TestErase();
    TestClear();
    TestReserve();
    TestArrayCombined();
    TestOtherDataType();
    TestNestedArrayWithPointers();
    TestNestedArray();
}