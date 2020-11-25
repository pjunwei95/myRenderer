#include "windowHandler.h"
#include "engine.h"
#include "drawScreen.h"
#include "logger.h"
#include "profileManager.h"

WindowHandler::WindowHandler()
    : m_Window{ NULL }, m_ScreenSurface{ NULL }
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

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
        //window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        //    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        m_Window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        if (m_Window == NULL)
        {
            logmsg("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 0;
        }
        else
        {
            m_Context = SDL_GL_CreateContext(m_Window);
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
        m_ScreenSurface = SDL_GetWindowSurface(m_Window);
    }

    {
        PROFILE_SCOPED(DrawScreen);
        //Fill the surface white
        drawScreen(m_ScreenSurface);
    }
}
void WindowHandler::updateWindow()
{
    PROFILE_FUNCTION();
    //Update the surface
    SDL_UpdateWindowSurface(m_Window);
    SDL_GL_SwapWindow(m_Window);
}
void WindowHandler::destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(m_Window);

    SDL_GL_DeleteContext(m_Context);

    //Quit SDL subsystems
    SDL_Quit();
}