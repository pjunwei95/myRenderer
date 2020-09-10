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
    //test();
    //testProfiling();
    //PROFILE_BEGIN(test1);
    beginProfile("test1");

    if(createWindow())
    {
        while (!getIsDone())
        {
            Timer timer;

            updateTimeStamp(&timer);

            drawWindow();

            getKeyInput();

            updateWindow();

            //profileFrameTime(&timer);

            idleUntilFPSLimit(&timer);
        }
        destroyWindow();
    }
    //PROFILE_END();
    endProfile();

}

