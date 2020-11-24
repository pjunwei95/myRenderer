#pragma once
#include "sdl/SDL.h"

typedef SDL_Window* WindowHandle;
typedef SDL_Surface* SurfaceHandle;

class WindowHandler
{
public:
    WindowHandler()
        : window{ NULL }, screenSurface{ NULL }
    {
    }

    bool createWindow();
    void drawWindow();
    void updateWindow();
    void destroyWindow();
private:
    //SDL Properties
    //The window we'll be rendering to
    WindowHandle window;
    //The surface contained by the window
    SurfaceHandle screenSurface;
};



