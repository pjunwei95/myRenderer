#include "array_unitTest.h"
#include "logger.h"
//TODO 
//Separate all of your testing code into files like "Array_UnitTest.h/cpp"
//
//You should run suites of unit tests based off the commandline
//unit tests will meticulously test every functionality of  your Array / Circular buffer etc, with hardcoded inputs, and will compare them with hard coded expected values to ensure nothing breaks



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
//
//void testArray1()
//{
//    LOG_UNIT_TEST();
//    
//    Array<int> a;
//    int num = 0;
//    //push 10 elements and print (init)
//    for (int i = 0; i < 10; ++i)
//    {
//        a.pushBack(num);
//        num++;
//    }
//    printTestArray(&a);
//
//    //print first
//    int getFirst = a.front();
//    logmsg("first = %d\n", getFirst);
//
//    //erase at idx
//    logmsg("erasing a[%d] = %d...\n", 6, a.at(6));
//    a.eraseAt(6);
//    logmsg("a[%d] is now = %d\n", 6, a.at(6));
//
//    //insert at idx
//    int newNum = 99;
//    logmsg("inserting a[%d] = %d...\n", 6, newNum);
//    a.insertAt(6, newNum);
//    logmsg("a[%d] is now = %d\n", 6, a.at(6));
//    printTestArray(&a);
//
//    //insert at idx
//    int anotherNum = 333;
//    logmsg("inserting a[%d] = %d...\n", 0, anotherNum);
//    a.insertAt(0, anotherNum);
//    logmsg("a[%d] is now = %d\n", 0, a.at(0));
//    printTestArray(&a);
//
//    //remove at fast idx 5
//    logmsg("RemoveAtFast 5...\n");
//    a.removeAtFast(5);
//    printTestArray(&a);
//
//    //remove last
//    logmsg("popping last element...\n");
//    a.popBack();
//
//    //print last
//    int getLast = a.back();
//    logmsg("last = %d\n", getLast);
//
//    //free after usage
//    //delete a;
// }
//
//void testArray2()
//{
//    LOG_UNIT_TEST();
//    // for circular buffer, without this constructors will give linker errors
//    Array<int> b;
//    b.reserve(10);
//    int num = 1;
//    b.pushBack(num);
//    num++;
//    b.pushBack(num);
//    num++;
//    //b->addSize(1);
//    b[0] = num;
//    logmsg("capacity of b = %d\n", b.capacity());
//    //int *num = b[0];
//    //for profiler
//}
//
//void testArrayClear()
//{
//    LOG_UNIT_TEST();
//    Array<int> container;
//    container.pushBack(1);
//    container.pushBack(2);
//    container.pushBack(3);
//
//
//    logmsg("Before clear:\n");
//    printTestArray(&container);
//    logmsg("Size = %d\n", container.size());
//
//    logmsg("Clear\n");
//    container.clear();
//
//    logmsg("After clear:\n");
//    printTestArray(&container);
//    logmsg("Size = %d\n", container.size());
//}

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
    //logmsg();
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

//void TestInsert() {
//    std::cout << "\n********** TestInsert **********\n";
//    my_vector a;
//    std::cout << "Empty array:\n";
//    Print(a);
//
//    std::cout << "push_back 5 integers:\n";
//    for (cs170::vector::value_type i = 0; i < 5; ++i) {
//        a.push_back(i);
//        Print(a);
//    }
//
//    // Insert value 99 in position 3
//    std::cout << "insert(3, 99):\n";
//    a.insert(3, 99);
//    Print(a);
//
//    // Insert value 98 in position 0
//    std::cout << "insert(0, 98):\n";
//    a.insert(0, 98);
//    Print(a);
//
//    // Insert value 97 in position 6
//    std::cout << "insert(6, 97):\n";
//    a.insert(6, 97);
//    Print(a);
//}
//
//
//// Another function to test CS170::vector::insert().
//// Two things to note:
//// First, notice that the my_vector object is created in a peculiar way.
//// Second, notice that if the insert function were to insert in a position
//// larger than the size of the current vector, it should abort the
//// program.
//void TestInsert1() {
//    std::cout << "\n********** TestInsert1 **********\n";
//    cs170::vector::value_type ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
//    cs170::vector::size_type size = sizeof(ia) / sizeof(*ia);
//    std::cout << "Construct from int array:\n";
//    my_vector org;
//
//    for (cs170::vector::size_type i = 0; i < size; ++i) {
//        org.push_back(ia[i]);
//    }
//    my_vector a(org);
//    Print(a);
//
//#if 0
//    // Supposed to cause abort
//    cs170::vector::size_type index = a.size() * 2;
//    std::cout << "insert integer at index " << index << ":\n";
//    a.insert(99, index);    // index too large, should cause abort
//#else
//    std::cout << "Not tested really...";
//    std::cout << "change the macro in ";
//    std::cout << " TestInsert1 to check" << std::endl;
//#endif
//}
//
//// This is the first in a series of functions that tests the subscript
//// operator. As can be observed, the subscript operator returns a
//// reference to the specific element given by the index, i.e., v[i] refers
//// to element in position i of the vector.
//void TestSubscripts() {
//    std::cout << "\n********** TestSubscripts **********\n";
//    my_vector a;
//
//    std::cout << "push_back 10 even integers:\n";
//    for (cs170::vector::value_type i = 0; i < 10; ++i) {
//        a.push_back(2 * i);
//    }
//
//    Print(a);
//    std::cout << "multiple each value by 3:\n";
//    for (cs170::vector::size_type i = 0; i < 10; ++i) {
//        a[i] = a[i] * 3;
//    }
//    Print(a);
//}
//
//// This is the second function that tests subscript operations.
//// Notice that the CS170::vector object is declared as read-only and
//// also constructed in a peculiar way.
//void TestSubscript1() {
//    std::cout << "\n********** TestSubscript1 **********\n";
//    cs170::vector::value_type
//        ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
//    cs170::vector::size_type size = sizeof(ia) / sizeof(*ia);
//    std::cout << "Construct from int array:\n";
//    my_vector org;
//
//    for (cs170::vector::size_type i = 0; i < size; ++i) {
//        org.push_back(ia[i]);
//    }
//    my_vector const a(org);
//    Print(a);
//
//    cs170::vector::size_type index = a.size() / 2;
//    std::cout << "using subscript: a[" << index << "]" << std::endl;
//    std::cout << "a[" << index << "] = " << a[index] << std::endl;
//}
//
//// This is the third function to test subscript operations.
//// The purpose of this function is to inform the implementor that the
//// subscript operator is supposed to cause an abort in the case when the
//// given position is not within the bounds of the CS170::vector.
//void TestSubscript2() {
//    std::cout << "\n********** TestSubscript2 **********\n";
//    cs170::vector::value_type ia[] = { 2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6 };
//    cs170::vector::size_type size = sizeof(ia) / sizeof(*ia);
//    std::cout << "Construct from int array:\n";
//    my_vector org;
//
//    for (cs170::vector::size_type i = 0; i < size; ++i) {
//        org.push_back(ia[i]);
//    }
//    my_vector const a(org);
//    Print(a);
//
//#ifdef TEST_SUBSCRIPT_2
//    //Supposed to cause abort
//    cs170::vector::size_type index = a.size() * 2;   // illegal
//    std::cout << "using subscript: a[" << index << "]" << std::endl;
//    std::cout << "a[" << index << "] = " << a[index] << std::endl;
//#else
//    std::cout << "Not tested really...";
//    std::cout << "change the macro in ";
//    std::cout << " TestSubscript2 to check" << std::endl;
//#endif
//}

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

//// This function tests the erase member function of class CS170::vector.
//// The main purpose of the erase function is to remove the element at
//// a given specific position in the vector.
//void TestErase() {
//    std::cout << "\n********** TestErase **********\n";
//    my_vector a;
//    std::cout << "Empty array:\n";
//    Print(a);
//
//    std::cout << "push_back 5 integers:\n";
//    for (cs170::vector::value_type i = 0; i < 5; ++i) {
//        a.push_back(i);
//        Print(a);
//    }
//
//    /*
//    Removing elements at position 0 and then 3.
//    */
//    // Remove elements at position 0 and then position 3
//    std::cout << "erase(0), erase(3):\n";
//    a.erase(0);
//    a.erase(3);
//    Print(a);
//}
//

void testArray()
{
    LOG_TEST(ARRAY);
    //testArray1();
    //testArray2();
    //testArrayClear();
    TestPush();
    TestCopy();
    TestAssign();
}