#include "profileManager.h"
#include "profileManager_unitTest.h"

#if 1
#define PROFILE_DEBUG() ProfileDebug()
#else
#define PROFILE_DEBUG()
#endif
void ProfileDebug()
{
    gs_ProfileManager.PrintStackProfile();
    gs_ProfileManager.clearStack();
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
    Sleep(33);
}

void OutsideDoubleDifferentNested()
{
    PROFILE_FUNCTION();
    DrawWindow();
    UpdateWindow();
    Sleep(33);
}

void DoubleSameNestedProfile()
{
    PROFILE_FUNCTION();
    DrawWindow();
    DrawWindow();
    //Sleep(33);
}

void ThisCallDrawWindow()
{
    PROFILE_FUNCTION();
    DrawWindow();
    Sleep(33);
}

void ThisCallUpdateWindow()
{
    PROFILE_FUNCTION();
    UpdateWindow();
    Sleep(33);
}

void NestedTwiceProfile()
{
    PROFILE_FUNCTION();
    ThisCallDrawWindow();
    ThisCallUpdateWindow();
    Sleep(33);
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
    ProfileDebug();
}

void testSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
    PROFILE_DEBUG(); //debug and cleanup the profile manager
}

void testSimpleNestedProfile()
{
    LOG_UNIT_TEST();
    OutsideSingleNested();
    PROFILE_DEBUG();
}

void testDoubleDifferentNestedProfile()
{
    LOG_UNIT_TEST();
    OutsideDoubleDifferentNested();
    PROFILE_DEBUG();
}

void testDoubleSameNestedProfile()
{
    LOG_UNIT_TEST();
    DoubleSameNestedProfile();
    PROFILE_DEBUG();
}

void testNestedTwiceProfile()
{
    LOG_UNIT_TEST();
    NestedTwiceProfile();
    PROFILE_DEBUG();
}

void testNonScopedBegin()
{
    LOG_UNIT_TEST();
    NonScopedBegin();
    PROFILE_DEBUG();
}


void testNonScopedNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedNestedBegin();
    PROFILE_DEBUG();
}

void testNonScopedNonNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedNonNestedBegin();
    PROFILE_DEBUG();
}


void testNonScopedDoubleNestedBegin()
{
    LOG_UNIT_TEST();
    NonScopedDoubleNestedBegin();
    PROFILE_DEBUG();
}

void testDoubleFrameSimpleProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 2; ++i)
    {
        DrawWindow();
        logmsg("Frame #%d:\n", i);
        PROFILE_DEBUG();
    }
}

void testDoubleFrameOutsideSingleNestedProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 2; ++i)
    {
        OutsideSingleNested();
        logmsg("Frame #%d:\n", i);
        PROFILE_DEBUG();
    }
}

void testFlipSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
    gs_ProfileManager.OnProfileFlip();
    gs_ProfileManager.PrintBufferProfile();
    gs_ProfileManager.clearBuffer();
}

void Foo()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 2; ++i)
    {
        DrawWindow();
        gs_ProfileManager.OnProfileFlip();
    }
    gs_ProfileManager.PrintBufferProfile();
    gs_ProfileManager.clearBuffer();
}


#define TEST 0
void testProfileManager()
{
    LOG_TEST(Profiler);
    //=========================================
    //ProfileTimer tests
    // Scoped
#if TEST
    testScoped();
    testSimpleProfile();
    testSimpleNestedProfile();
    testDoubleDifferentNestedProfile();
    testDoubleSameNestedProfile();
    testNestedTwiceProfile();
    // Non-scoped
    testNonScopedBegin();
    testNonScopedNestedBegin();
    testNonScopedNonNestedBegin();
    testNonScopedDoubleNestedBegin();
#else
    //=========================================
    //Multiple-frame tests
    //testDoubleFrameSimpleProfile();
    //testDoubleFrameOutsideSingleNestedProfile();
    testFlipSimpleProfile();
    Foo();
    //testProfileCircularBuffer();
#endif
}