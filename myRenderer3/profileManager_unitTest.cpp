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
    ProfileManager::Instance().PrintStackProfile();
    ProfileManager::Instance().ClearStack();
}

void ProfileBufferDebug()
{
    ProfileManager::Instance().PrintBufferProfile();
    ProfileManager::Instance().ClearBuffer();
}

//====================================================
//Simulated Real Functions

void Scoped()
{
    Sleep(33);
}

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

void OutsideDoubleSameNestedNonScopedProfile()
{
    PROFILE_FUNCTION();
    DrawWindow();
    DrawWindow();
}

void OutsideDoubleSameNestedScopedProfile()
{
    PROFILE_FUNCTION();
    {
        PROFILE_SCOPED(Scoped1);
        Scoped();
    }
    {
        PROFILE_SCOPED(Scoped2);
        Scoped();
    }
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


void NonScopedBegin()
{
    PROFILE_BEGIN(test);
    Scoped();
    PROFILE_END(test);
}

void NonScopedNestedBegin()
{
    PROFILE_BEGIN(Test);
    Scoped();
    {
        PROFILE_BEGIN(CalledBeforeTestEndProfile);
        Scoped();
        PROFILE_END(CalledBeforeTestEndProfile);
    }
    PROFILE_END(Test);
}

void NonScopedNonNestedBegin()
{
    PROFILE_BEGIN(Test);
    Scoped();
    PROFILE_END(Test);

    PROFILE_BEGIN(CalledAfterTestEndProfile);
    Scoped();
    PROFILE_END(CalledAfterTestEndProfile);
}

void NonScopedDoubleNestedBegin()
{
    PROFILE_BEGIN(GfxRenderTask);
    Scoped();
    {
        PROFILE_BEGIN(MergeCMDListRecord);
        Scoped();
        {
            PROFILE_BEGIN(DrawWaterVisibilityForQuery_CPU);
            Scoped();
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

void testDoubleSameNestedNonScopedProfile()
{
    LOG_UNIT_TEST();
    OutsideDoubleSameNestedNonScopedProfile();
    PROFILE_STACK_DEBUG();
}

void testDoubleSameNestedScopedProfile()
{
    LOG_UNIT_TEST();
    OutsideDoubleSameNestedScopedProfile();
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
    ProfileManager::Instance().OnProfileFlip();
    PROFILE_BUFFER_DEBUG();
}

void testMultipleFlipSimpleProfile()
{
    LOG_UNIT_TEST();
    logmsg("Call DrawWindow for 6 frames\n");
    for (int i = 0; i < 6; ++i)
    {
        DrawWindow();
        ProfileManager::Instance().OnProfileFlip();
    }
    PROFILE_BUFFER_DEBUG();
}

void testMultipleFlipNestedTwiceProfile()
{
    LOG_UNIT_TEST();
    for (int i = 0; i < 6; ++i)
    {
        NestedTwiceProfile();
        ProfileManager::Instance().OnProfileFlip();
    }
    PROFILE_BUFFER_DEBUG();
}


#define TEST 1
void testProfileManager()
{
    LOG_TEST(Profiler);
    //=========================================
    //Single-frame tests
#if TEST
    // Function-Scoped
    //testSimpleProfile();
    //testSimpleNestedProfile();
    //testDoubleDifferentNestedProfile();
    testDoubleSameNestedScopedProfile();
    testDoubleSameNestedNonScopedProfile();
#else
    testNestedTwiceProfile();
    // Scoped
    testScoped();
    // Non-scoped
    testNonScopedBegin();
    testNonScopedNestedBegin();
    testNonScopedNonNestedBegin();
    testNonScopedDoubleNestedBegin();
    //=========================================
    LOG_TEST(ProfileCircularBuffer);
    logmsg("Profile Buffer Size = 3\n");
    //=========================================
    //Multiple-frame tests
    testDoubleFrameSimpleProfile();
    testDoubleFrameOutsideSingleNestedProfile();
    // With Circular Buffer
    testSingleFlipSimpleProfile();
    testMultipleFlipSimpleProfile();
    testMultipleFlipNestedTwiceProfile();

#endif
}