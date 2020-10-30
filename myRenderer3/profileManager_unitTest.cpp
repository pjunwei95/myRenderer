#include "profileManager_unitTest.h"

#define PROFILE_THIS() ProfileTimer entry##__COUNTER__(__FUNCTION__); 

void DrawWindow()
{
    PROFILE_THIS();
    Sleep(33);
}

void testSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
    gs_ProfileManager.PrintProfile();
}

void testProfileManager()
{
    LOG_TEST(Profiler);

    //With Macros
#if PROFILE_MACRO
    testSimpleProfileWithMacro();
#else
    //Without Macros
    testSimpleProfile();
    //testSimpleNestedProfile();
    //testDoubleDifferentNestedProfile();
    //testDoubleSameNestedProfile();
    //testNestedTwiceProfile();
#endif
    //for multiple frames
    //testProfileCircularBuffer();
}