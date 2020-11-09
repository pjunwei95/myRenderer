#include "sdl/SDL.h"
#include "engine.h"
#include "windowHandler.h"
#include <stdio.h>
#include "drawScreen.h"
#include "logger.h"
#include "profileManager.h"

//WindowHandle window;
//SurfaceHandle screenSurface;

void WindowHandler::initWindow()
{
    //SDL Properties
    //The window we'll be rendering to
    window = NULL;
    //The surface contained by the window
    screenSurface = NULL;
}
// bool initWindow(WindowHandle windowHandle)
bool WindowHandler::createWindow()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logmsg("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            logmsg("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void WindowHandler::drawWindow()
{
    PROFILE_FUNCTION();

    {
        PROFILE_SCOPED(GetWindowSurface);
        //Get window surface
        screenSurface = SDL_GetWindowSurface(window);
    }

    {
        PROFILE_SCOPED(DrawScreen);
        //Fill the surface white
        drawScreen(screenSurface);
    }
}
void WindowHandler::updateWindow()
{
    PROFILE_FUNCTION();
    //Update the surface
    SDL_UpdateWindowSurface(window);
}
void WindowHandler::destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();
}