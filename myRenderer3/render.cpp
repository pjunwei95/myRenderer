//#define GLEW_STATIC
#include "include/GL/glew.h"
#include "include/sdl/SDL_opengl.h"
#include "include/sdl/SDL_opengles2.h"
#include "logger.h"

const char* vertexShaderSource = "shader.vert";
const char *fragmentShaderSource = "shader.frag";

void render()
{
    glewExperimental = GL_TRUE;
    glewInit();


    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    logmsg("%u\n", vertexBuffer);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);



}
