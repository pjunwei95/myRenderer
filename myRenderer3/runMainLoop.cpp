#include <stdio.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"
#include "windowHandler.h"


void runMainLoop()
{
    initialiseTimer();
    
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
    }
    destroyWindow();
}

