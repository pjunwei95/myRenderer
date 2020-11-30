#include "render.h"
#include "fileManager.h"
#include "array.h"

#ifdef BREAKPOINT_ENABLED
#pragma optimize("",off)
#endif

//TODO macro to debug each glCalls

const GLchar* vertexSource = "shader.vert";
const GLchar* fragmentSource = "shader.frag";

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    //TODO asserts
    userParam;
    length;
    source;
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
}

void CheckProgramStatus(GLuint shaderProgram, GLenum pname, const char* identifier)
{
    GLint status;
    glGetProgramiv(shaderProgram, pname, &status);
    char msg[CHAR_MAX_LIMIT];
    glGetProgramInfoLog(shaderProgram, CHAR_MAX_LIMIT, NULL, msg);
    if (!strlen(msg))
        logmsg("%s OK!\n", identifier);
    else
        logmsg("%s: %s", identifier, msg);
    assert(status == GL_TRUE);
}

void CheckShaderCompilation(GLuint shader, const char* fileName) 
{
    assert(fileName);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    char msg[CHAR_MAX_LIMIT];
    glGetShaderInfoLog(shader, CHAR_MAX_LIMIT, NULL, msg);
    if (!strlen(msg))
        logmsg("%s compiled successfully!\n", fileName);
    else
        logmsg("%s compilation failed!: %s", fileName, msg);
    assert(status == GL_TRUE);
}


GLuint CompileShader(const char* shaderFile, ShaderType shaderType)
{
    FileManager fm(shaderFile, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    char* code = (char*)malloc(fm.GetBufferLength());
    fm.ReadBufferWithLength(code, fm.GetBufferLength());

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    CheckShaderCompilation(shader, shaderFile);
    free(code);

    return shader;
}

//Wrap up a shaderProgram class

void InitGraphics()
{
    //set contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    assert(err == GLEW_OK);

    logmsg("Status: Using GLEW %s.\n", glewGetString(GLEW_VERSION));
    logmsg("System supports OpenGL %s\n", glGetString(GL_VERSION));

    if (Engine::Instance().GetOption() == Engine::Option::DEBUG)
        glEnable(GL_DEBUG_OUTPUT);

    assert(glDebugMessageCallback);
    logmsg("Register OpenGL debug callback\n");
    glDebugMessageCallback(MessageCallback, nullptr);

    //Filter debug messages
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
    //========================ErrorTypes:
    //GL_DEBUG_TYPE_ERROR
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);
    //GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, NULL, GL_TRUE);
    //GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, GL_DONT_CARE, 0, NULL, GL_TRUE);
    //========================Severity
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, NULL, GL_TRUE);

    //Create and compile the shaders
    GLuint vertexShader = CompileShader(vertexSource, ShaderType::VERTEX);
    GLuint fragmentShader = CompileShader(fragmentSource, ShaderType::FRAGMENT);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    CheckProgramStatus(shaderProgram, GL_LINK_STATUS, STRINGIFY(GL_LINK_STATUS));
    glValidateProgram(shaderProgram);
    CheckProgramStatus(shaderProgram, GL_VALIDATE_STATUS, STRINGIFY(GL_VALIDATE_STATUS));
    glUseProgram(shaderProgram);

    //to be extracted
#if 1

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };

    //Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#endif
#if 1
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
#endif
}

