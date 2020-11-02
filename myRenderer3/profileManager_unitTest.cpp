#include "profileManager.h"
#include "profileManager_unitTest.h"

#if 1
#define PROFILE_DEBUG() ProfileDebug()
#else
#define PROFILE_DEBUG()
#endif
void ProfileDebug()
{
    gs_ProfileManager.PrintProfile();
    gs_ProfileManager.clearProfileManager();
}

//====================================================
//Simulated Real Functions

void DrawWindowBeginEnd()
{
    PROFILE_BEGIN("Sample begin");
    Sleep(33);
    PROFILE_END();

    PROFILE_BEGIN("Another Begin");
    Sleep(33);
    PROFILE_END();
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
    Sleep(33);
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

//====================================================
//Tests
void testScoped()
{
    LOG_UNIT_TEST();
    {
        PROFILE_SCOPED("test scoped");
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


void testProfileBegin()
{
    LOG_UNIT_TEST();
    DrawWindowBeginEnd();
    PROFILE_DEBUG();
}

void testProfileManager()
{
    LOG_TEST(Profiler);
    //=========================================
    //ProfileTimer tests
    // Scoped
    testScoped();
    testSimpleProfile();
    testSimpleNestedProfile();
    testDoubleDifferentNestedProfile();
    testDoubleSameNestedProfile();
    testNestedTwiceProfile();
    // Begin End
    testProfileBegin();

    //for multiple frames
    //testProfileCircularBuffer();
}