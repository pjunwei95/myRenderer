#include "renderer.h"
#include "profileManager.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"


#ifdef BREAKPOINT_ENABLED
#pragma optimize("",off)
#endif

const char* vertexSource = "res/shader.vert";
const char* fragmentSource = "res/shader.frag";

Renderer::Renderer()
    : m_Window{ nullptr }, m_ScreenSurface{ nullptr }, m_Context{ nullptr }
{
    InitGraphics();
}

Renderer::~Renderer()
{
    //TODO delete shaders and programs

    DestroyWindow();
}

void Renderer::DrawTriangle()
{
    //================================================================
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
    glBindFragDataLocation(shaderProgram.GetProgramID(), 0, "outColor");

    // Specify the layout (vertex format) of the vertex data
    VertexBufferFormat layout;
    layout.Push(shaderProgram.GetProgramID(), "position", 2);
    layout.Push(shaderProgram.GetProgramID(), "color", 3);

    VertexArray va;
    va.AddBuffer(vb, layout);
    //================================================================

    m_ScreenSurface = SDL_GetWindowSurface(m_Window);

    shaderProgram.Bind();
    va.Bind();
    vb.Bind();

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Draw(VertexArray const& va, VertexBuffer const& vb, Shader const& shader)
{
    PROFILE_FUNCTION();
    m_ScreenSurface = SDL_GetWindowSurface(m_Window);

    shader.Bind();
    va.Bind();
    vb.Bind();

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen to black
}

void Renderer::SwapBuffer() const
{
    PROFILE_FUNCTION();
    SDL_GL_SwapWindow(m_Window);
}

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

void Renderer::InitGraphics()
{
    CreateSDLWindow();

    //set contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    assert(err == GLEW_OK);
    if (Engine::Instance().GetOption() == Engine::Option::DEBUG)
    {
        logmsg("Status: Using GLEW %s.\n", glewGetString(GLEW_VERSION));
        logmsg("System supports OpenGL %s\n", glGetString(GL_VERSION));

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
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::CreateSDLWindow()
{
    //Initialize SDL
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    //Create window
    m_Window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    assert(m_Window);

    m_Context = SDL_GL_CreateContext(m_Window);
}

void Renderer::DestroyWindow()
{
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window); //Destroy window
    SDL_Quit(); //Quit SDL subsystems
}


