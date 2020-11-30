#include "render.h"
#include "fileManager.h"
#include "array.h"

#ifdef BREAKPOINT_ENABLED
#pragma optimize("",off)
#endif

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

void LogShaderCompilation(GLuint shader, const char* fileName) 
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    char log[512];
    glGetShaderInfoLog(shader, 512, NULL, log);
    if (!strlen(log))
        logmsg("%s compiled successfully!\n", fileName);
    else
        logmsg("%s compilation failed!: %s", fileName, log);
}

//void LogShaderCompilation(GLuint shader)
//{
//    GLint status;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
//    char log[512];
//    glGetShaderInfoLog(shader, 512, NULL, log);
//    if (!strlen(log))
//        logmsg("Compiled successfully!\n");
//    else
//        logmsg("Compilation failed!: %s\n", log);
//}


void InitGraphics()
{
    //set contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);

#if 1
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


#if 1
     //Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);

  GLfloat vertices[] = {
       0.0f,  0.5f,
       0.5f, -0.5f,
      -0.5f, -0.5f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#endif


#ifdef SHADER_OBJ
    Shader vShaderObj;
    vShaderObj.m_FileName = vertexSource;
    FileManager foo(vShaderObj.m_FileName, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    vShaderObj.m_BufferLength = foo.GetBufferLength();
    vShaderObj.m_Buffer = (char*)malloc(vShaderObj.m_BufferLength);
    foo.ReadBufferWithLength(vShaderObj.m_Buffer, vShaderObj.m_BufferLength);
    vShaderObj.m_Shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderObj.m_Shader, 1, &vShaderObj.m_Buffer, NULL);
    glCompileShader(vShaderObj.m_Shader);
    LogShaderCompilation(vShaderObj.m_Shader);
#else
    FileManager vertexFM(vertexSource, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    char* vertexCode = (char*)malloc(vertexFM.GetBufferLength());
    vertexFM.ReadBufferWithLength(vertexCode, vertexFM.GetBufferLength());

    //Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    LogShaderCompilation(vertexShader, vertexSource);
#endif

    FileManager fragmentFM(fragmentSource, FileManager::TYPE_TEXT, FileManager::MODE_READ);
    char* fragmentCode = (char*)malloc(fragmentFM.GetBufferLength());
    fragmentFM.ReadBufferWithLength(fragmentCode, fragmentFM.GetBufferLength());

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    LogShaderCompilation(fragmentShader, fragmentSource);

    free(vertexCode);
    free(fragmentCode);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
#ifdef SHADER_OBJ
    glAttachShader(shaderProgram, vShaderObj.m_Shader);
#else
    glAttachShader(shaderProgram, vertexShader);
#endif
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    //to be extracted
#if 1
        // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

#endif

#else
// Initialize GLEW
glewExperimental = GL_TRUE;
glewInit();

// Create Vertex Array Object
GLuint vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

// Create a Vertex Buffer Object and copy the vertex data to it
GLuint vbo;
glGenBuffers(1, &vbo);

GLfloat vertices[] = {
     0.0f,  0.5f,
     0.5f, -0.5f,
    -0.5f, -0.5f
};

glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


FileManager vertexFM(vertexSource, FileManager::TYPE_TEXT, FileManager::MODE_READ);
char* vertexCode = (char*)malloc(vertexFM.GetBufferLength());
vertexFM.ReadBufferWithLength(vertexCode, vertexFM.GetBufferLength());

FileManager fragmentFM(fragmentSource, FileManager::TYPE_TEXT, FileManager::MODE_READ);
char* fragmentCode = (char*)malloc(fragmentFM.GetBufferLength());
fragmentFM.ReadBufferWithLength(fragmentCode, fragmentFM.GetBufferLength());

// Create and compile the vertex shader
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexCode, NULL);
glCompileShader(vertexShader);

// Create and compile the fragment shader
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
glCompileShader(fragmentShader);

// Link the vertex and fragment shader into a shader program
GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glBindFragDataLocation(shaderProgram, 0, "outColor");
glLinkProgram(shaderProgram);
glUseProgram(shaderProgram);

// Specify the layout of the vertex data
GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
#endif

}
