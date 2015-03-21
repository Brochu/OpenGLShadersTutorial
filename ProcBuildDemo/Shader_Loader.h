#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

class Shader_Loader
{
private:
    std::string readShader(char* filename);
    GLuint createShader(GLenum shaderType,
        std::string source,
        char* shaderName);

public:
    Shader_Loader();
    ~Shader_Loader();

    GLuint createProgram(char* vertexShaderFilename,
        char* fragmentShaderFilename);
};