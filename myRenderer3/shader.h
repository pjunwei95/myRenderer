#pragma once
enum ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader 
{
public:
    Shader(const char* vertexFilePath, const char* fragmentFilePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    inline uint32_t GetProgramID() { return m_RendererID; }
private:
    uint32_t m_RendererID;

    uint32_t CompileShader(const char* shaderFile, ShaderType shaderType);
    uint32_t CreateShader(const char* vertexShader, const char* fragmentShader);
};
