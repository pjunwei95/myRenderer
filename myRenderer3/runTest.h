#pragma once
#include <crtdbg.h>
#include "array_unitTest.h"
#include "stack_unitTest.h"
#include "profileManager_unitTest.h"
#include "circularBuffer_unitTest.h"

void runTest()
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    // TESTS
    testProfileManager();
    //testArray();
    //testCircularBuffer();
}