#include <stdio.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profiler.h"
//#include "test.h"
#include "circularBuffer.h"

void runMainLoop()
{
    FrameRateController frc;
    frc.initialiseTimer();
    initProfile(50);
    //testCircularBuffer();
    //testProfiler();
    //beginProfile("createWindow");

    WindowHandler wh;

    if(wh.createWindow())
    {
        //endProfile();

        while (!getIsDone())
        {
            beginProfile("beforeIdle");

            Timer timer;

            frc.updateTimeStamp(&timer);

            wh.drawWindow();

            getKeyInput();

            beginProfile("updateWindow");

            wh.updateWindow();

            frc.idleUntilFPSLimit(&timer);
            endProfile();
            endProfile();
        }
        wh.destroyWindow();
    }
    destroyProfile();

}

