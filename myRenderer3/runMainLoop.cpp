#include <stdio.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"

void runMainLoop()
{
    TimerHandle test2;
    TimerHandle* nFrequency = &test2;

    TimerHandle test3;
    TimerHandle* defaultFrameTime = &test3;

    QueryPerformanceFrequency(nFrequency); //to be called only once. not per frame

    // 1s = 1 000 000 micro s = 30 frames
    defaultFrameTime->QuadPart = 1000000 / FPS; // unit is in seconds, NOT microseconds

    //SDL Properties
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            while (!getIsDone())
            {
                TimerHandle test;
                TimerHandle* nStartTime = &test;
                StartTimer(nStartTime);

                //Get window surface
                screenSurface = SDL_GetWindowSurface(window);

                //Fill the surface white
                drawScreen(screenSurface);

                getKeyInput();

                //Update the surface
                SDL_UpdateWindowSurface(window);
                //Wait two seconds
                //SDL_Delay(2000);

                while (1) // frame drawing and blocking, or at gameStateCurr == next
                {
                    TimerHandle test4;
                    TimerHandle* nStopTime = &test4;

                    StopTimer(nStopTime);

                    if (isWithinFrameRate(nStartTime, nStopTime, nFrequency, defaultFrameTime))
                    {
                        //printf("frametime = %.2f ms\n", GetTimerElapsedMs(nStopTime));
                        //printf("frametime = %f s\n", GetTimerElapsedSeconds(nStopTime));
                        printf("FPS = %f \n", 1.0 / GetTimerElapsedSeconds(nStopTime));
                        break;
                    }

                }
            }
        }
    }
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}