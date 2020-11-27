#include "drawScreen.h"

void DrawScreen(SDL_Surface * screenSurface)
{
    //fill rectangle on screen
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
}


void DrawTriangle(WindowHandle window)
{
    // Create Vertex Array Object
    //GLuint vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    //// Create a Vertex Buffer Object and copy the vertex data to it
    //GLuint vbo;
    //glGenBuffers(1, &vbo);

    //GLfloat vertices[] = {
    //     0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    //};

    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}
