#pragma once

struct Shader
{
    const char* m_FileName = 0;
    char* m_Buffer = 0;
    long m_BufferLength = 0;
    GLuint m_Shader;
};

void InitGraphics();
