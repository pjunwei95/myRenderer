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
    //PROFILE_BEGIN(test1);
    //beginProfile("createWindow");

    WindowHandler wh;

    if(wh.createWindow())
    {
        //endProfile();

        while (!getIsDone())
        {
            beginProfile("beforeidle");

            Timer timer;

            updateTimeStamp(&timer);

            wh.drawWindow();

            getKeyInput();

            wh.updateWindow();
            endProfile();

            //profileFrameTime(&timer);

            idleUntilFPSLimit(&timer);
        }
        wh.destroyWindow();
    }
    //PROFILE_END();

}

