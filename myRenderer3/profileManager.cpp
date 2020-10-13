//#include "profileManager.h"
//#include <stdio.h>
//#include <assert.h>
//#include "logger.h"
//#include "array.h"
//#include "circularBuffer.h"
//#include "stack.h"
//
//void ProfileManager::initProfile(uint32_t frameNum)
//{
//    frc.initialiseTimer();
//    isProfileBegin = false;
//    profileStack = new Stack<Profile>();
//    frameCircBuf = new CircularBuffer<Array<Profile>>(frameNum);
//}
//
//Profile* ProfileManager::getProfile()
//{
//    Profile* profile = (Profile*)profileStack->peek();
//    assert(profile);
//    return profile;
//}
//
//void ProfileManager::beginProfile(const char* string)
//{
//    assert(string);
//    assert(!isProfileBegin);
//    isProfileBegin = true;
//
//    Profile profile;
//    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
//    frc.updateTimeStamp(&profile.m_Start);
//    profileStack->push(&profile);
//}
//
//void ProfileManager::endProfile()
//{
//    assert(isProfileBegin);
//    isProfileBegin = false;
//
//    //dereference from peek()
//    Profile* profile = getProfile();
//
//    //update time elapsed
//    frc.updateTimeStamp(&profile->m_Elapsed);
//    frc.calcTimerElapsedUs(&profile->m_Elapsed, &profile->m_Start);
//
//    profileStack->pop();
//}
//
//void ProfileManager::onProfilerFlip()
//{
//    //create vector of profile for each frame
//    //frame profile vector
//    //Array fpVec = createNewArray(sizeof(Profile));
//    Array<Profile>* fpVec = new Array<Profile>();
//
//    //iterate thru all profiles
//    for (uint32_t i = 0; i < profileStack->size(); ++i)
//    {
//        Profile* ptrToProfile = (Profile*) profileStack->at(i);
//         //update time elapsed
//        frc.updateTimeStamp(&ptrToProfile->m_Elapsed);
//        frc.calcTimerElapsedUs(&ptrToProfile->m_Elapsed, &ptrToProfile->m_Start);
//        fpVec->pushBack(ptrToProfile);
//    }
//
//    //push array to circular buffer
//    if (frameCircBuf->isFull())
//    {
//         //when something is popped from circular buffer, it needs to be freed.
//        Array<Profile>* ptrFpVec = (Array<Profile>*) frameCircBuf->popFront();
//        ptrFpVec;
//        //TODO handle memleak
//        //freeArray(ptrFpVec);
//        //delete ptrFpVec;
//    }
//    //pushBackCircBuf(&frameCircBuf, &fpVec);
//    frameCircBuf->pushBack(fpVec);
//    
//}
//
//void ProfileManager::destroyProfile()
//{
//    //profile stack is destructed
//    delete profileStack;
//
//    //TODO fix mem leak here for each array
//    //Array<Profile>* foo = frameCircBuf->popFrontCircBuf();
//    //delete foo;
//
//    //free circular buffer
//    delete frameCircBuf;
//}
//
//void ProfileManager::printPastFrames()
//{
//    int tempFront = frameCircBuf->frontIndex();
//    int size = frameCircBuf->size();
//
//    for (int i = 0; i < size; ++i)
//    {
//        //go through each frame in circular buffer
//        int idx = (tempFront + i) % frameCircBuf->capacity();
//
//        //Array frameProfileList = *((Array*)frameCircBuf->getCircBufAt(&frameCircBuf, idx));
//        Array<Profile>* frameProfileList = (Array<Profile>*)frameCircBuf->at(idx);
//        for (uint32_t j = 0; j < frameProfileList->size(); ++j)
//        {
//            Profile* ptrToProfile = (Profile*)frameProfileList->at(j);
//            Profile profile = *ptrToProfile;
//            logmsg("Frame #%d, Time elapsed for |%s| profile = %.2f ms\n", i, profile.m_ProfileName, frc.getTimerElapsedMs(&profile.m_Elapsed));
//            //formatting for profiler: frame#, profileName, startTime, endTime
//            //logmsg("#%d, %s, %.2f\n", i, profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
//        }
//    }
//}
//
//void ProfileManager::testProfiler()
//{
//    uint32_t frameNum = 3;
//    initProfile(frameNum);
//    for (uint32_t i = 0; i < frameNum; ++i)
//    {
//        beginProfile(__FUNCDNAME__);
//        {
//            //beginProfile("nested");
//            //simulate one frame = 33ms has passed
//            Sleep(10);
//            onProfilerFlip();
//            //endProfile();
//        }
//        endProfile();
//    }
//    printPastFrames();
//
//    destroyProfile();
//}
//
