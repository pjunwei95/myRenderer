#include "renderer.h"
#include "fileManager.h"
#include "array.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

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
    vb.Bind();

    Shader shaderProgram(vertexSource, fragmentSource);
    shaderProgram.Bind();
    //glBindFragDataLocation(shaderProgram.GetProgramID(), 0, "outColor");

    // Specify the layout (vertex format) of the vertex data
    VertexBufferFormat layout;
    layout.Push(shaderProgram.GetProgramID(), "position", 2);
    layout.Push(shaderProgram.GetProgramID(), "color", 3);

    VertexArray va;
    va.AddBuffer(vb, layout);
}

void DestroyGraphics()
{

}

