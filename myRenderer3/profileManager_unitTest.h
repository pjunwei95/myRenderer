#pragma once
#include "profileManager.h"
//
//#define UNIT_TEST_PRINT()ProfileEntry* first = gs_ProfileManager.GetStack().at(0);\
//                            ProfileEntry ancestor = *first;\
//                            PrintProfile(ancestor, 0);
//
////////////////////////////////////////////////////////////////
////Simulated main functions
//
////draw and update functions profile entry are the same 
//ProfileEntry gs_Foo{ "Foo" };
//void DrawWindow()
//{
//    ProfileEntry gs_DrawWindowProfileTag{ "DrawWindowProfileTag" };
//    ProfileTimer test(gs_DrawWindowProfileTag);
//    NewBeginProfile(test);
//    Sleep(33);
//    NewEndProfile(test);
//}
//
//void testSimpleProfile()
//{
//    LOG_UNIT_TEST();
//    DrawWindow();
//    //UNIT_TEST_PRINT();
//    //ProfileEntry* first = gs_ProfileManager.GetStack().at(0);
//    //ProfileEntry ancestor = *first;
//    //PrintProfile(ancestor, 0);
//    gs_ProfileManager.Clear();
//}
//
//
//void OutsideSingleNested()
//{
//    /*BeginProfile(gs_Foo);
//    ///
//    Stopwatch timerTest;
//    timerTest.start();
//    DrawWindow();
//    timerTest.stop();
//    gs_Foo.m_Duration = timerTest.getDurationMs();
//    ///
//    EndProfile(gs_Foo);*/
//
//    ProfileEntry gs_Bar{ "Bar" };
//    ProfileTimer test(gs_Bar);
//    NewBeginProfile(test);
//    ///
//    DrawWindow();
//    ///
//    NewEndProfile(test);
//}
//
//void testSimpleNestedProfile()
//{
//    LOG_UNIT_TEST();
//    OutsideSingleNested();
//    //ProfileEntry* first = gs_ProfileManager.GetStack().at(0); 
//    //ProfileEntry ancestor = *first;
//    //PrintProfile(ancestor, 0);
//    gs_ProfileManager.Clear();
//}

//ProfileEntry gs_UpdateWindowProfileTag{ "UpdateWindowProfileTag" };
//void UpdateWindow()
//{
//    BeginProfile(gs_UpdateWindowProfileTag);
//    //Separate timer functions
//    Stopwatch timer;
//    timer.start();
//
//    Sleep(33);
//    timer.stop();
//    gs_UpdateWindowProfileTag.m_Duration = timer.getDurationMs();
//
//    EndProfile(gs_UpdateWindowProfileTag);
//}
//
//void OutsideDoubleDifferentNested()
//{
//    BeginProfile(gs_Foo);
//    ///
//    Stopwatch timerTest;
//    timerTest.start();
//    DrawWindow();
//    UpdateWindow();
//    timerTest.stop();
//    gs_Foo.m_Duration = timerTest.getDurationMs();
//    ///
//    EndProfile(gs_Foo);
//}
//
//void testDoubleDifferentNestedProfile()
//{
//    LOG_UNIT_TEST();
//    OutsideDoubleDifferentNested();
//    ProfileEntry* first = gs_ProfileManager.GetStack().at(0);
//    PrintProfile(*first, 0);
//    gs_Foo.Clear();
//    gs_ProfileManager.Clear();
//}
//
//void OutsideDoubleSameNested()
//{
//    BeginProfile(gs_Foo);
//    ///
//    Stopwatch timerTest;
//    timerTest.start();
//    DrawWindow();
//    DrawWindow();
//    timerTest.stop();
//    gs_Foo.m_Duration = timerTest.getDurationMs();
//    ///
//    EndProfile(gs_Foo);
//}
//
//void testDoubleSameNestedProfile()
//{
//    LOG_UNIT_TEST();
//    OutsideDoubleSameNested();
//    ProfileEntry* first = gs_ProfileManager.GetStack().at(0);
//    PrintProfile(*first, 0);
//    gs_Foo.Clear();
//    gs_ProfileManager.Clear();
//}
//
//ProfileEntry gs_TCDWProfileTag{ "gs_TCDWProfileTag" };
//void ThisCallDrawWindow()
//{
//    BeginProfile(gs_TCDWProfileTag);
//    ///
//    Stopwatch timerTest;
//    timerTest.start();
//    DrawWindow();
//    timerTest.stop();
//    gs_TCDWProfileTag.m_Duration = timerTest.getDurationMs();
//    ///
//    EndProfile(gs_TCDWProfileTag);
//}
//
//
//void OutsideNestedTwiceNested()
//{
//    BeginProfile(gs_Foo);
//    ///
//    Stopwatch timerTest;
//    timerTest.start();
//    ThisCallDrawWindow();
//    timerTest.stop();
//    gs_Foo.m_Duration = timerTest.getDurationMs();
//    ///
//    EndProfile(gs_Foo);
//}
//
//void testNestedTwiceProfile()
//{
//    LOG_UNIT_TEST();
//    OutsideNestedTwiceNested();
//    ProfileEntry* first = gs_ProfileManager.GetStack().at(0);
//    PrintProfile(*first, 0);
//    gs_Foo.Clear();
//    gs_ProfileManager.Clear();
//}
//
//
///////////////////////////////////////////////////////////
////Macros
//void DrawWindowWithMacro()
//{
//    PROFILE_BEGIN(DrawWindowProfile);
//    ///
//    Sleep(33);
//    ///
//    PROFILE_END(DrawWindowProfile);
//    PROFILE_PRINT(DrawWindowProfile);
//
//}
//
//void testSimpleProfileWithMacro()
//{
//    LOG_UNIT_TEST();
//    DrawWindowWithMacro();
//    gs_ProfileManager.Clear();
//}
//
//
//void testProfileCircularBuffer()
//{
//
//}
void testProfileManager();

