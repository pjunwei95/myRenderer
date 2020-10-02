#include "engine.h"
#include "getKeyInput.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profiler.h"
////#include "test.h"

void runMainLoop()
{
    FrameRateController frc;
    frc.initialiseTimer();
    initProfile(50);
    testProfiler();
    //beginProfile("createWindow");

    WindowHandler wh;

    if(wh.createWindow())
    {
        //endProfile();

        while (!getIsDone())
        {
            //beginProfile("beforeIdle");

            Timer timer;

            frc.updateTimeStamp(&timer);

            wh.drawWindow();

            getKeyInput();

            //beginProfile("updateWindow");

            wh.updateWindow();
            //endProfile();

            frc.idleUntilFPSLimit(&timer);
            //endProfile();
            //endProfile();
        }
        wh.destroyWindow();
    }
    //destroyProfile();

}

