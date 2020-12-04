//deprecated
#ifdef DEPRECATED
#include "windowHandler.h"
#include "drawScreen.h"
#include "profileManager.h"
#include "renderer.h"

//TODO convert this to graphics manager class
//these should all belong to your Graphics Engine, not Window class
//actually, if anything, Window Creation should now belong to GraphicInit

WindowHandler::WindowHandler()
    : m_Window{ NULL }, m_ScreenSurface{ NULL }
{
    createWindow();
}

WindowHandler::~WindowHandler()
{
    DestroyWindow();
}

void WindowHandler::createWindow()
{
    //Initialize SDL
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    //logmsg("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

    //Create window
    m_Window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    assert(m_Window);
    //logmsg("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    //logmsg("SDL Error: %s\n", SDL_GetError());

    m_Context = SDL_GL_CreateContext(m_Window);
}

void WindowHandler::DrawWindow()
{
    PROFILE_FUNCTION();

    //Get window surface
    m_ScreenSurface = SDL_GetWindowSurface(m_Window);
    {
        PROFILE_SCOPED(DrawTriangle);
        DrawTriangle();
        //Fill the surface white
        //drawScreen(m_ScreenSurface);
    }
}
void WindowHandler::UpdateWindow()
{
    PROFILE_FUNCTION();
    //Update the surface
    //SDL_UpdateWindowSurface(m_Window);

    //Swap buffers
    SDL_GL_SwapWindow(m_Window);
}
void WindowHandler::DestroyWindow()
{
    SDL_GL_DeleteContext(m_Context);

    //Destroy window
    SDL_DestroyWindow(m_Window);

    //Quit SDL subsystems
    SDL_Quit();
}
#endif
