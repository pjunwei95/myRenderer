#pragma once
#include "profileManager.h"

//////////////////////////////////////////////////////////////
//Simulated main functions

ProfileEntry gs_DrawWindowProfileTag{ "DrawWindowProfileTag" };
ProfileEntry gs_Foo{ "Foo" };
void DrawWindow()
{
    BeginProfile(gs_DrawWindowProfileTag);
    //Separate timer functions
    Stopwatch timer;
    timer.start();

    Sleep(33);
    timer.stop();
    gs_DrawWindowProfileTag.m_Duration = timer.getDurationMs();

    EndProfile(gs_DrawWindowProfileTag);
    logmsg("End of scope, drawWindow took %.2f ms\n", gs_DrawWindowProfileTag.m_Duration);
}

void Outside()
{
    BeginProfile(gs_Foo);
    ///
    Stopwatch timerTest;
    timerTest.start();
    DrawWindow();
    DrawWindow();
    timerTest.stop();
    gs_Foo.m_Duration = timerTest.getDurationMs();
    ///
    EndProfile(gs_Foo);
    PrintProfile(&gs_Foo, 0);
}

void testSimpleProfile()
{
    LOG_UNIT_TEST();
    DrawWindow();
}

void testNestedProfile()
{
    LOG_UNIT_TEST();
    Outside();
}
/////////////////////////////////////////////////////////
//Macros
void DrawWindowWithMacro()
{
    PROFILE_BEGIN(DrawWindowProfile);
    ///
    Sleep(33);
    ///
    PROFILE_END(DrawWindowProfile);
    PROFILE_PRINT(DrawWindowProfile);
}


void OutsideWithMacro()
{
    PROFILE_BEGIN(Bar);
    ///
    DrawWindowWithMacro();
    DrawWindowWithMacro();
    ///
    PROFILE_END(Bar);
    PROFILE_PRINT(Bar);
}

void testSimpleProfileWithMacro()
{
    LOG_UNIT_TEST();
    DrawWindowWithMacro();
}

void testNestedProfileWithMacro()
{
    LOG_UNIT_TEST();
    OutsideWithMacro();
}

void testProfileCircularBuffer()
{

}

void testProfileManager()
{
    LOG_TEST(Profiler);
    //Without Macros
    testSimpleProfile();
    testNestedProfile();
    //With Macros
#if PROFILE_MACRO
    testSimpleProfileWithMacro();
    testNestedProfileWithMacro();
#endif
    //for multiple frames
    testProfileCircularBuffer();
}