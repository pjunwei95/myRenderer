//#pragma once
//#include "logger.h"
////#include <string>
//#include "frameRateController.h"
//#define CHAR_MAX_LIMIT 256
//
////------------------------------------------------------------------------
//class Profile
//{
//public:
//    Profile(const char* name,
//        void(*cbBegin)(Profile*) = nullptr,
//        void(*cbEnd)(Profile*) = nullptr
//    )
//        :
//        cbBegin{ cbBegin }, cbEnd{ cbEnd }
//    {
//        strcpy_s(m_Name, sizeof(m_Name), name);
//        if (cbBegin)
//            cbBegin(this);
//    }
//    ~Profile()
//    {
//        if (cbEnd)
//            cbEnd(this);
//    }
//    void(*cbBegin)(Profile*);
//    void(*cbEnd)(Profile*);
//
//    const char* getString() { return m_Name; }
//
//private:
//    char m_Name[CHAR_MAX_LIMIT];
//    Timer m_Start;
//    Timer m_Elapsed;
//};
////------------------------------------------------------------------------
//
//
//void ProfileBegin(Profile* profile)
//{
//    logmsg("Profile Begin: %s\n", profile->getString());
//        frc.updateTimeStamp(&profile.m_Start);
//
//}
//
//void ProfileEnd(Profile* profile)
//{
//    logmsg("Profile End: %s\n", profile->getString());
//
//}
//#define PROFILE_SCOPED() \
//Profile __timer__{__FUNCSIG__, &ProfileBegin, &ProfileEnd}
//
//void func1()
//{
//    PROFILE_SCOPED();
//    logmsg("func1\n");
//}
//void testProfile()
//{
//    logmsg("===========================\n");
//    func1();
//    //func2();
//    logmsg("===========================\n");
//}
//
