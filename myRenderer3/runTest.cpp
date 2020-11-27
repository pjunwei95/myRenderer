#include <crtdbg.h>
#include "array_unitTest.h"
#include "stack_unitTest.h"
#include "profileManager_unitTest.h"
#include "circularBuffer_unitTest.h"
#include "unit_test_math.h"

void ExecuteAllTests()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // TESTS
    //TestArray();
    //testCircularBuffer();
    TestProfileManager();
    TestMath();
}