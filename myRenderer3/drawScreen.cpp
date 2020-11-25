#include "drawScreen.h"
#include "include/sdl/SDL_opengl.h"

void DrawScreen(SDL_Surface * screenSurface)
{
    //fill rectangle on screen
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
}


void DrawTriangle(WindowHandle window)
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}
