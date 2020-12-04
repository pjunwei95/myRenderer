#pragma once
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"

class Renderer
{
public:
    typedef SDL_Window* WindowHandle;
    typedef SDL_Surface* SurfaceHandle;

    Renderer();
    ~Renderer();

    void DrawTriangle();
    void Draw(VertexArray const& va, VertexBuffer const& vb, Shader const& shader);
    void SwapBuffer() const;
    void Clear() const;
private:
    //SDL Properties
    WindowHandle m_Window; //The window we'll be rendering to
    SurfaceHandle m_ScreenSurface;  //The surface contained by the window
    SDL_GLContext m_Context;

    void InitGraphics();
    void CreateSDLWindow();
    void DestroyWindow();
};