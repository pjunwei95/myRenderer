#include "profileManager.h"
#include "profileManager_unitTest.h"

#if 1
#define PROFILE_STACK_DEBUG() ProfileStackDebug()
#define PROFILE_BUFFER_DEBUG() ProfileBufferDebug()
#else
#define PROFILE_DEBUG()
#define PROFILE_BUFFER_DEBUG()
#endif
void ProfileStackDebug()
{
    gs_ProfileManager.PrintStackProfile();
    gs_ProfileManager.clearStack();
}

void ProfileBufferDebug()
{
    gs_ProfileManager.PrintBufferProfile();
    gs_ProfileManager.clearBuffer();
}

//====================================================
//Simulated Real Functions

void DrawWindow()
{
    PROFILE_FUNCTION();
    Sleep(33);
}

void UpdateWindow()
{
    PROFILE_FUNCTION();
    Sleep(33);
}

void OutsideSingleNested()
{
    PROFILE_FUNCTION();
    DrawWindow();
}

void OutsideDoubleDifferentNested()
{
    PROFILE_FUNCTION();
    DrawWindow();
    UpdateWindow();
}

void DoubleSameNestedProfile()
{
    PROFILE_FUNCTION();
    DrawWindow();
    DrawWindow();
}

void ThisCallDrawWindow()
{
    PROFILE_FUNCTION();
    DrawWindow();
}

void ThisCallUpdateWindow()
{
    PROFILE_FUNCTION();
    UpdateWindow();
}

void NestedTwiceProfile()
{
    PROFILE_FUNCTION();
    ThisCallDrawWindow();
    ThisCallUpdateWindow();
}

void DoSomething()
{
    Sleep(33);
}


void NonScopedBegin()
{
    PROFILE_BEGIN(test);
    DoSomething();
    PROFILE_END(test);
}

void NonScopedNestedBegin()
{
    PROFILE_BEGIN(Test);
    DoSomething();
    {
        PROFILE_BEGIN(CalledBeforeTestEndProfile);
        DoSomething();
        PROFILE_END(CalledBeforeTestEndProfile);
    }
    PROFILE_END(Test);
}

void NonScopedNonNestedBegin()
{
    PROFILE_BEGIN(Test);
    DoSomething();
    PROFILE_END(Test);

    PROFILE_BEGIN(CalledAfterTestEndProfile);
    DoSomething();
    PROFILE_END(CalledAfterTestEndProfile);
}

void NonScopedDoubleNestedBegin()
{
    PROFILE_BEGIN(GfxRenderTask);
    DoSomething();
    {
        PROFILE_BEGIN(MergeCMDListRecord);
        DoSomething();
        {
            PROFILE_BEGIN(DrawWaterVisibilityForQuery_CPU);
            DoSomething();
            PROFILE_END(DrawWaterVisibilityForQuery_CPU);
        }
        PROFILE_END(MergeCMDListRecord);
    }
    PROFILE_END(GfxRenderTask);
}


//====================================================
//Tests
void testScoped()
{
    LOG_UNIT_TEST();
    {
        PROFILE_SCOPED(Scoped);
        Sleep(33);
    }
    PROFILE_STACK_DEBUG(); 
}

void testSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
    PROFILE_STACK_DEBUG(); //debug and cleanup the profile manager
}

void testSimpleNestedProfile()
{
    LOG_UNIT_TEST();
    OutsideSingleNested();
    PROFILE_STACK_DEBUG();
}

void testDoubleDifferentNestedProfile()
{
    LOG_UNIT_TEST();
    OutsideDoubleDifferentNested();
    PROFILE_STACK_DEBUG();
}

void testDoubleSameNestedProfile()
{
    LOG_UNIT_TEST();
    DoubleSameNestedProfile();
    PROFILE_STACK_DEBUG();
}

void testNestedTwiceProfile()
{
    LOG_UNIT_TEST();
    NestedTwiceProfile();
    PROFILE_STACK_DEBUG();
}

void testNonScopedBegin()
{
    LOG_UNIT_TEST();
    NonScopedBegin();
    PROFILE_STACK_DEBUG();
}


void testNonScopedNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedNestedBegin();
    PROFILE_STACK_DEBUG();
}

void testNonScopedNonNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedNonNestedBegin();
    PROFILE_STACK_DEBUG();
}


void testNonScopedDoubleNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedDoubleNestedBegin();
    PROFILE_STACK_DEBUG();
}

void testDoubleFrameSimpleProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 2; ++i)
    {
        DrawWindow();
        logmsg("Frame #%d:\n", i);
        PROFILE_STACK_DEBUG();
    }
}

void testDoubleFrameOutsideSingleNestedProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 2; ++i)
    {
        OutsideSingleNested();
        logmsg("Frame #%d:\n", i);
        PROFILE_STACK_DEBUG();
    }
}

void testSingleFlipSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
    gs_ProfileManager.OnProfileFlip();
    PROFILE_BUFFER_DEBUG();
}

void testMultipleFlipSimpleProfile()
{
    LOG_UNIT_TEST();
    logmsg("Call DrawWindow for 6 frames\n");
    for (int i = 0; i < 6; ++i)
    {
        DrawWindow();
        gs_ProfileManager.OnProfileFlip();
    }
    PROFILE_BUFFER_DEBUG();
}

void testMultipleFlipNestedTwiceProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 6; ++i)
    {
        NestedTwiceProfile();
        gs_ProfileManager.OnProfileFlip();
    }
    PROFILE_BUFFER_DEBUG();
}


#define TEST 1
void testProfileManager()
{
    LOG_TEST(Profiler);
    //=========================================
    //gs_ProfileTimer tests
#if TEST
    // Function-Scoped
    //testSimpleProfile();
    testSimpleNestedProfile();
    testDoubleDifferentNestedProfile();
    testDoubleSameNestedProfile();
    testNestedTwiceProfile();
#else
    // Scoped
    testScoped();
    // Non-scoped
    testNonScopedBegin();
    testNonScopedNestedBegin();
    testNonScopedNonNestedBegin();
    testNonScopedDoubleNestedBegin();
    //=========================================
    //Multiple-frame tests
    logmsg("Profile Buffer Size = 3\n");
    testDoubleFrameSimpleProfile();
    testDoubleFrameOutsideSingleNestedProfile();
    // With Circular Buffer
    testSingleFlipSimpleProfile();
    testMultipleFlipSimpleProfile();
    testMultipleFlipNestedTwiceProfile();

#endif
}