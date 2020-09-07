#include <stdio.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profiler.h"

void runMainLoop()
{
    initialiseTimer();
    PROFILE_CAPTURE(mainLoop);

    if(createWindow())
    {
        while (!getIsDone())
        {
            Timer timer;

            updateTimeStamp(&timer);

            drawWindow();

            getKeyInput();

            updateWindow();

            idleUntilFPSLimit(&timer);
        }
        destroyWindow();
    }
    PROFILE_END();
}

