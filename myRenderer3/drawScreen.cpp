#include "sdl/SDL.h"
#include "drawScreen.h"

void drawScreen(SDL_Surface * screenSurface)
{
    //fill rectangle on screen
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

}
