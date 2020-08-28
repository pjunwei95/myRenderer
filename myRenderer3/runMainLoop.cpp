#include <stdio.h>
#include <windows.h>

#include "sdl/SDL.h"
#include "engine.h"
#include "drawScreen.h"
#include "getKeyInput.h"
#include "runMainLoop.h"
#include "frameRateController.h"

void runMainLoop()
{
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
                frameStart();

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
                    frameEnd();

                    if (isWithinFrameRate())
                        break;
                }
            }
        }
    }
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}