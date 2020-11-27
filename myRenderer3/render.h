#pragma once

//#define SHADER_OBJ

#ifdef SHADER_OBJ
struct Shader
{
    const char* m_FileName = 0;
    char* m_Buffer = 0;
    long m_BufferLength = 0;
    GLuint m_Shader;
};
#endif

void InitGraphics();
