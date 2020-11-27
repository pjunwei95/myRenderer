#include "windowHandler.h"
#include "drawScreen.h"
#include "profileManager.h"

WindowHandler::WindowHandler()
    : m_Window{ NULL }, m_ScreenSurface{ NULL }
{
    //set contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS , SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
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
        DrawTriangle(m_Window);
        //Fill the surface white
        //drawScreen(m_ScreenSurface);
    }
}
void WindowHandler::updateWindow()
{
    PROFILE_FUNCTION();
    //Update the surface
    SDL_UpdateWindowSurface(m_Window);
}
void WindowHandler::destroyWindow()
{
    SDL_GL_DeleteContext(m_Context);

    //Destroy window
    SDL_DestroyWindow(m_Window);

    //Quit SDL subsystems
    SDL_Quit();
}