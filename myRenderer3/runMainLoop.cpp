#include <stdio.h>
#include <windows.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"

LARGE_INTEGER test;
LARGE_INTEGER * nStartTime = &test;


// Windows properties
LARGE_INTEGER test2;
LARGE_INTEGER *nFrequency = &test2;

LARGE_INTEGER test3;
LARGE_INTEGER *defaultFrameTime = &test3;

LARGE_INTEGER test4;
LARGE_INTEGER * nStopTime = &test4;


void runMainLoop()
{

    

    QueryPerformanceFrequency(nFrequency); //to be called only once. not per frame

    // 1s = 1 000 000 micro s = 30 frames
    defaultFrameTime->QuadPart = 1000000 / FPS; //frametime is in micro seconds


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
                    //frameEnd(nStopTime);
                    StopTimer(nStopTime);

                    if (isWithinFrameRate(nStopTime, nStartTime, nFrequency, defaultFrameTime))
                    {
                        //printf("%.2f\n", (float)nStopTime->QuadPart / 1000);
                        //printf("%.2f\n", GetTimerElapsedMs(nStartTime,nStopTime,nFrequency));

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