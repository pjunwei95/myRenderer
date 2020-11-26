#include "include/GL/glew.h"
#include "include/sdl/SDL_opengl.h"
#include "fileManager.h"

#pragma optimize("",off)

const GLchar* vertexSource = "shader.vert";
const GLchar* fragmentSource = "shader.frag";

//const GLchar* vertexSource = R"glsl(
//    #version 150 core
//    in vec2 position;
//    void main()
//    {
//        gl_Position = vec4(position, 0.0, 1.0);
//    }
//)glsl";
//const GLchar* fragmentSource = R"glsl(
//    #version 150 core
//    out vec4 outColor;
//    void main()
//    {
//        outColor = vec4(1.0, 1.0, 1.0, 1.0);
//    }
//)glsl";


void render()
{
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

    //Checks for compilation
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    char vertexlog[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, vertexlog);
    logmsg("Vertex compilation %s", vertexlog);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    char fragmentlog[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, fragmentlog);
    logmsg("Fragment compilation %s", fragmentlog);

    free(vertexCode);
    free(fragmentCode);



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

}
