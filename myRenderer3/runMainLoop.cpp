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
    initialiseTimer();
    initProfile();
    //testCircularBuffer();
    //testProfiler();
    beginProfile("createWindow");

    WindowHandler wh;

    if(wh.createWindow())
    {
        endProfile();

        while (!getIsDone())
        {
            beginProfile("beforeIdle");

            Timer timer;

            updateTimeStamp(&timer);

            wh.drawWindow();

            getKeyInput();

            wh.updateWindow();
            endProfile();

            idleUntilFPSLimit(&timer);
        }
        wh.destroyWindow();
    }
    destroyProfile();
    //PROFILE_END();

}

