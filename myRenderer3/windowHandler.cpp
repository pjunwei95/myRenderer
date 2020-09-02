#include "sdl/SDL.h"
#include "engine.h"
#include "windowHandler.h"
#include <stdio.h>
#include "drawScreen.h"

WindowHandle window;
SurfaceHandle screenSurface;

void initWindow()
{
    //SDL Properties
    //The window we'll be rendering to
    window = NULL;
    //The surface contained by the window
    screenSurface = NULL;
}
// bool initWindow(WindowHandle windowHandle)
bool createWindow()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void drawWindow()
{
    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    //Fill the surface white
    drawScreen(screenSurface);
}
void updateWindow()
{
    //Update the surface
    SDL_UpdateWindowSurface(window);
}
void destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();
}