#pragma once
typedef SDL_Window* WindowHandle;
typedef SDL_Surface* SurfaceHandle;

class WindowHandler
{
public:
    WindowHandler();
    ~WindowHandler();

    bool createWindow();
    void drawWindow();
    void updateWindow();
    void DestroyWindow();
private:
    //SDL Properties
    //The window we'll be rendering to
    WindowHandle m_Window;
    //The surface contained by the window
    SurfaceHandle m_ScreenSurface;
    SDL_GLContext m_Context;
};



