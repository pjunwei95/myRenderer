#pragma once
#include "sdl/SDL.h"

typedef SDL_Window* WindowHandle;
typedef SDL_Surface* SurfaceHandle;

class WindowHandler
{
public:
    void initWindow();
    bool createWindow();
    void drawWindow();
    void updateWindow();
    void destroyWindow();

private:
    WindowHandle window;
    SurfaceHandle screenSurface;
};



