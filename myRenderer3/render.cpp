#include "render.h"
#include "fileManager.h"
#include "array.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

#ifdef BREAKPOINT_ENABLED
#pragma optimize("",off)
#endif

const GLchar* vertexSource = "res/shader.vert";
const GLchar* fragmentSource = "res/shader.frag";

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    logmsg("---------------------Callback-----------------\n");
    logmsg("message: %s\ntype: ", message);
    const char* errorTypeStr = 0;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        errorTypeStr = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        errorTypeStr = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        errorTypeStr = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        errorTypeStr = "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        errorTypeStr = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        errorTypeStr = "OTHER";
        break;
    default:
        errorTypeStr = "** GL ERROR **";
        logmsg("0x%x", type);
        break;
    }
    logmsg("%s\nid: %i\nseverity: ", errorTypeStr, id);
    const char* severityStr = 0;
    switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
        severityStr = "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severityStr = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        severityStr = "HIGH";
        break;
    }
    logmsg("%s\n\n", severityStr);
    assert(source);
    assert(length);
    assert(userParam);
}

void CheckShaderCompilation(GLuint shader, const char* fileName)
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

void CheckProgramStatus(GLuint shaderProgram, GLenum pname, const char* identifier)
{
    GLint status;
    glGetProgramiv(shaderProgram, pname, &status);
#if 1
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
#else
    char msg[CHAR_MAX_LIMIT];
    glGetProgramInfoLog(shaderProgram, CHAR_MAX_LIMIT, NULL, msg);
    if (!strlen(msg))
        logmsg("%s OK!\n", identifier);
    else
        logmsg("%s:\n%s\n", identifier, msg);
#endif
    assert(status == GL_TRUE);
}


GLuint CompileShader(const char* shaderFile, ShaderType shaderType)
{
    assert(shaderFile);

    FileManager fm(shaderFile, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    Array<GLchar> shaderCode;
    fm.ReadArray(shaderCode);

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode.GetData(), NULL);
    //glShaderSource(shader, 1, &shaderFile, NULL);
    glCompileShader(shader);
    CheckShaderCompilation(shader, shaderFile);

    return shader;
}


static GLuint CreateShaderProgram()
{
    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();

    //Create and compile the shaders
    GLuint vertexShader = CompileShader(vertexSource, ShaderType::VERTEX);
    GLuint fragmentShader = CompileShader(fragmentSource, ShaderType::FRAGMENT);

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


//TODO Wrap up a shaderProgram class

void InitGraphics()
{
    //set contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    assert(err == GLEW_OK);

    logmsg("Status: Using GLEW %s.\n", glewGetString(GLEW_VERSION));
    logmsg("System supports OpenGL %s\n", glGetString(GL_VERSION));

    if (Engine::Instance().GetOption() == Engine::Option::DEBUG)
        glEnable(GL_DEBUG_OUTPUT);

    assert(glDebugMessageCallback);
    logmsg("Registered OpenGL debug callback\n");
    glDebugMessageCallback(MessageCallback, nullptr);

    //Filter debug messages
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    //========================ErrorTypes:
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PORTABILITY, GL_DONT_CARE, 0, NULL, GL_FALSE);
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, NULL, GL_FALSE);
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, NULL, GL_FALSE);
    //========================Severity
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, NULL, GL_FALSE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);


    GLfloat vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    VertexBuffer vb(vertices, sizeof(vertices));

    GLuint shaderProgram = CreateShaderProgram();
    glBindFragDataLocation(shaderProgram, 0, "outColor");//TODO extract this out?
    glUseProgram(shaderProgram);


    //Specify input vertex format for vertex shader
    // Specify the layout of the vertex data
    VertexArray va;
    VertexBufferFormat layout;
    layout.Push(shaderProgram, "position", 2);
    layout.Push(shaderProgram, "color", 3);
    va.AddBuffer(vb, layout);


#if 0
    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);
#endif
}

void DestroyGraphics()
{

}

