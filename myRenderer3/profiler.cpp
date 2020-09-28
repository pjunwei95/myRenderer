#include "profiler.h"
#include <stdio.h>
#include <assert.h>
#include "logger.h"
#include "array.h"
#include "circularBuffer.h"

Array profileStack;
Array circBuffProfileList;

void initProfile()
{
    profileStack = createNewArray(sizeof(Profile));
    circBuffProfileList = createNewArray(sizeof(CircularBuffer));
}

void beginProfile(const char * string)
{
    Profile profile;
    strcpy_s(profile.m_ProfileName, sizeof(profile.m_ProfileName), string); //easy conversion to macros
    updateTimeStamp(&profile.m_Start);
    pushBackArray(&profileStack, &profile); // stack push
}

void endProfile()
{
    assert(!isArrayEmpty(&profileStack));
    //dereference from peek()
    Profile profile = *((Profile*)getArrayBack(&profileStack));
    updateTimeStamp(&profile.m_Elapsed);
    calcTimerElapsedUs(&profile.m_Elapsed, &profile.m_Start);

    logmsg("Time elapsed for |%s| profile = %.2f ms\n", 
        profile.m_ProfileName, getTimerElapsedMs(&profile.m_Elapsed));
    popBackArray(&profileStack); //stack pop
}

void testProfiler()
{
    initialiseTimer();
    initProfile();
    beginProfile("test1");
        //beginProfile("test2");
        //Sleep(100);
        //endProfile();
    Sleep(100);
    endProfile();

}

//logging begins to log for profile of this nameString
    //circular buffer of frametime belonging to those with identifier 
    //string of profileName. so it requires attributes of both profileName
    //and profileTimeElapsed. so maybe an vector of circularBuffers?


    //Vector< CicularBuffer<Profile> > listOfCircularBufferProfile
    //CircularBuffer bar = createNewCircBuf(50, sizeof(Profile));
    //Array circBuffProfileList = createNewArray(sizeof(CircularBuffer));

    //design considerations:
    //to add array on init - yes
    //to add circular buffer on init - no
    //add identifier to circular buffer on init - no
    // on new begin profile, add identifier to circular buffer - no
    // on new endprofile, add identifier to circular buffer - yes

    //somewhere

    // add dummy stuff to array with name contained inside
    //baz.timeElapsed = 0
    //baz.start = 0;
    //baz.name = name;
    //bar.push(baz)
    // foo.pushback(bar)

    //Pseudo
    //Vector< CicularBuffer<Profile> > listOfCircularBufferProfile
    //check if profileName exist in vector of circ buffer
    //if not, push a new circular buffer into array
    //if have, go to its circular buffer and push new time elapsed

bool circBuffContains(CircularBuffer* cb, char* stringName)
{
    cb;
    stringName;
    return false;
}

void function(Profile* profile) 
{
    //check if array empty
    if (isArrayEmpty(&circBuffProfileList))
    {
        //do new creation of circular buffer
        CircularBuffer newCircBuff = createNewCircBuf(50, sizeof(profile));

        //add new dummy profile
        Profile dummyProfile;
        strcpy_s(dummyProfile.m_ProfileName, sizeof(profile->m_ProfileName), profile->m_ProfileName);
        dummyProfile.m_Elapsed = profile->m_Elapsed;
        pushBackCircBuf(&newCircBuff, &dummyProfile);
        
    } 
    else // array !empty
    { 
        //check if profileName exist in vector of circ buffer
        // loop thru vector of circ buffer
        int numCircBuff = getArraySize(&circBuffProfileList);
        for (int i = 0; i < numCircBuff; ++i)
        {
            //Vector< CicularBuffer<Profile> > listOfCircularBufferProfile

            // circBuff = arr[i]
            CircularBuffer* baz = (CircularBuffer*)getArrayAt(&circBuffProfileList, i);

            //if not, push a new circular buffer into array
            //!if circBuff.contains(name)
            if (!circBuffContains(baz, profile->m_ProfileName))
            {
                // add dummy stuff to array with name contained inside
                //baz.timeElapsed = 0
                //baz.start = 0;
                //baz.name = name;
                //bar.push(baz)
                // foo.pushback(bar)
            }
            //else if have, go to its circular buffer and push new time elapsed

                //at the endprofilesection
                //ba.name = name;
                //ba.timeelap = time...
                //baz.push(ba)

        }
    }
}

void destroyProfiles();

