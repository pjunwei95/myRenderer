#include "shader.h"
#include "fileManager.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
    : m_RendererID{ 0 }
{
    m_RendererID = CreateShader(vertexFilePath,fragmentFilePath);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void CheckShaderCompilation(uint32_t shader, const char* fileName)
{
    assert(fileName);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        Array<GLchar> message;
        message.reserve(length);
        glGetShaderInfoLog(shader, length, &length, message.GetData());
        logmsg("Failed to compile %s\n%s\n", fileName, message.GetData());

        glDeleteShader(shader); //before asserting to delete resources
    }
    assert(status == GL_TRUE);
}

uint32_t Shader::CompileShader(const char* shaderFile, ShaderType shaderType)
{
    //parse shader
    assert(shaderFile);
    FileManager fm(shaderFile, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    Array<char> shaderCode;
    fm.ReadArray(shaderCode);

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode.GetData(), NULL);
    glCompileShader(shader);
    CheckShaderCompilation(shader, shaderFile);

    return shader;
}

void CheckProgramStatus(GLuint shaderProgram, GLenum pname, const char* identifier)
{
    GLint status;
    glGetProgramiv(shaderProgram, pname, &status);
    if (status != GL_TRUE)
    {
        int length;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
        Array<GLchar> message;
        message.reserve(length);
        glGetProgramInfoLog(shaderProgram, message.capacity(), &length, message.GetData());
        logmsg("%s FAILED\n%s\n", identifier, message.GetData());
        glDeleteProgram(shaderProgram);
    }
    assert(status == GL_TRUE);
}

uint32_t Shader::CreateShader(const char* vertexFilePath, const char* fragmentFilePath)
{
    // Link the vertex and fragment shader into a shader program
    uint32_t shaderProgram = glCreateProgram();

    //Create and compile the shaders
    uint32_t vertexShader = CompileShader(vertexFilePath, ShaderType::VERTEX);
    uint32_t fragmentShader = CompileShader(fragmentFilePath, ShaderType::FRAGMENT);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    CheckProgramStatus(shaderProgram, GL_LINK_STATUS, STRINGIFY(GL_LINK_STATUS));
    glValidateProgram(shaderProgram);
    CheckProgramStatus(shaderProgram, GL_VALIDATE_STATUS, STRINGIFY(GL_VALIDATE_STATUS));

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    return shaderProgram;
}
