#pragma once
#include <crtdbg.h>
#include "array_unitTest.h"
#include "stack_unitTest.h"
#include "circularBuffer.h"
#include "profileManager.h"
#include "test.h"


void runTest()
{
    // Enable run-time memory check for debug builds.
    //#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //#endif

    //int * pi = new int;
    //pi;

    // TESTS
    testProfileManager();
    //testStack();
    //testArray();
    //testCircularBuffer();
}