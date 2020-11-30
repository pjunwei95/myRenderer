#include "windowHandler.h"
#include "drawScreen.h"
#include "profileManager.h"
#include "render.h"

//TODO convert this to graphics manager class
WindowHandler::WindowHandler()
    : m_Window{ NULL }, m_ScreenSurface{ NULL }
{
    if (createWindow())
        InitGraphics();
}

WindowHandler::~WindowHandler()
{
    DestroyWindow();
}

bool WindowHandler::createWindow()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logmsg("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        //Create window
        //window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        //    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        m_Window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        if (m_Window == NULL)
        {
            logmsg("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            m_Context = SDL_GL_CreateContext(m_Window);
            return true;
        }
    }
}

void WindowHandler::drawWindow()
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
void WindowHandler::updateWindow()
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

