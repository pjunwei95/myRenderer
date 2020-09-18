#include <stdio.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profiler.h"
#include "test.h"

void runMainLoop()
{
    initialiseTimer();
    initProfile();
    test();
    //testProfiler();
    //PROFILE_BEGIN(test1);
    beginProfile("createWindow");

    if(createWindow())
    {
        endProfile();

        while (!getIsDone())
        {
            //beginProfile("beforeidle");

            Timer timer;

            updateTimeStamp(&timer);

            drawWindow();

            getKeyInput();

            updateWindow();
            //endProfile();

            //profileFrameTime(&timer);

            idleUntilFPSLimit(&timer);
        }
        destroyWindow();
    }
    //PROFILE_END();

}

