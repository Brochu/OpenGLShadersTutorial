#include "Shader_Loader.h"
#include <iostream>
#include <fstream>
#include <vector>

Shader_Loader::Shader_Loader(){  }
Shader_Loader::~Shader_Loader(){  }

std::string Shader_Loader::readShader(char* filename)
{
    std::string shaderCode;
    std::ifstream file(filename, std::ios::in);

    if (!file.good())
    {
        std::cout << "Could not read file : " << filename << std::endl;
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shaderCode.resize((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shaderCode[0], shaderCode.size());
    file.close();

    return shaderCode;
}

GLuint Shader_Loader::createShader(GLenum shaderType,
    std::string source,
    char* filename)
{
    int compileResult = 0;
    GLuint shader = glCreateShader(shaderType);
    const char* shaderCodePtr = source.c_str();
    const int shaderCodeSize = source.size();

    glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    // Check for errors (top kek)
    if (compileResult == GL_FALSE)
    {
        int logInfoLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logInfoLength);
        std::vector<char> shaderLog(logInfoLength);
        glGetShaderInfoLog(shader, logInfoLength, NULL, &shaderLog[0]);
        std::cout << "Error compiling shader : " << filename << std::endl;
        std::cout << &shaderLog[0] << std::endl;
        return 0;
    }

    return shader;
}

GLuint Shader_Loader::createProgram(char* vertexShaderFilename,
    char* fragmentShaderFilename)
{
    std::string vertexShaderCode = readShader(vertexShaderFilename);
    std::string fragmentShaderCode = readShader(fragmentShaderFilename);

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

    int linkResult = 0;
    // create program handle
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

    // Check for link errors
    if (linkResult == GL_FALSE)
    {
        int infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
        std::cout << "Shader Loader link error: " << std::endl;
        std::cout << &programLog[0] << std::endl;
        return 0;
    }

    return program;
}