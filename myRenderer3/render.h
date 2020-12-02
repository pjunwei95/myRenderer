#pragma once







struct ShaderProgram
{
    GLuint m_Vbo;
    GLuint m_Vao;
    GLuint m_vShader; 
    GLuint m_fShader;
    GLuint m_Program;
};

enum ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

void InitGraphics();
