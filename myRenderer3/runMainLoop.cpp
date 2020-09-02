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
            //LARGE_INTEGER test;
            Timer nStartTime;
            startTimer(&nStartTime);

            drawWindow();

            getKeyInput();

            updateWindow();

            while (1) // frame drawing and blocking, or at gameStateCurr == next
            {
                Timer nStopTime;
                stopTimer(&nStopTime);

                if (isWithinFrameRate(&nStartTime, &nStopTime))
                {
                    //printf("frametime = %.2f ms\n", GetTimerElapsedMs(nStopTime));
                    //printf("frametime = %f s\n", GetTimerElapsedSeconds(nStopTime));
                    //printf("FPS = %f \n", 1.0 / getTimerElapsedSeconds(&nStopTime));
                    break;
                }

            }
        }
    }
    destroyWindow();
}