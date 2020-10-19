#include "engine.h"
#include "getKeyInput.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include <crtdbg.h>
//#include "profiler.h"
//#include "test.h"

bool isTestProfile = false;

void runMainLoop()
{
    // Enable run-time memory check for debug builds.
    //#if defined(DEBUG) | defined(_DEBUG)
    //_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //#endif

    //int * pi = new int;
    //pi;

    FrameRateController frc;
    frc.initialiseTimer();
  
    //if (isTestProfile)
        //initProfile(50);   

    //if (!isTestProfile)
        //testProfiler();

    //beginProfile("createWindow");

    WindowHandler wh;

    if(wh.createWindow())
    {
        //endProfile();

        while (!getIsDone())
        {
            //beginProfile("beforeIdle");

            Timer timer;

            frc.updateTimeStamp(timer);

            wh.drawWindow();

            getKeyInput();

            //if (isTestProfile)
                //beginProfile("updateWindow");

            wh.updateWindow();


            frc.idleUntilFPSLimit(timer);

            //if (isTestProfile)
                //onProfilerFlip();
            
            //if (isTestProfile)
                //endProfile();
            //endProfile();
        }
        wh.destroyWindow();
    }
    //if (isTestProfile)
        //destroyProfile();

}

