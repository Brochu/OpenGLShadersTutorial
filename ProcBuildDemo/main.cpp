// OpenGL related includes
#include <GL\glew.h>
#include <GL\freeglut.h>

// IO includes
#include <iostream>

// Shaders related includes
#include "Shader_Loader.h"

// Defines
#define uchar unsigned char

GLuint program_red_triangle;
GLuint program_green_triangle;

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // use the created program
    glUseProgram(program_red_triangle);
    // draw 3 vertices as triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // use second created program
    glUseProgram(program_green_triangle);
    // draw 3 vertices as points
    glDrawArrays(GL_POINTS, 0, 3);

    glutSwapBuffers();
}

void keyboardEventHandler(uchar key, int x, int y){
    std::cout << key << std::endl;
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    // Load and compile shaders
    Shader_Loader shaderLoader;
    program_red_triangle = shaderLoader.createProgram("Vertex_Shader.glsl", "Fragment_Shader_Red.glsl");
    program_green_triangle = shaderLoader.createProgram("Vertex_Shader.glsl", "Fragment_Shader_Green.glsl");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(5.0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(500, 500);
    glutInitWindowSize(800, 600);
    glutCreateWindow("My First OpenGL Window");
    glewInit();

    init();

    // Register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardEventHandler);

    glutMainLoop();
    glDeleteProgram(program_red_triangle);
    glDeleteProgram(program_green_triangle);
    return 0;
}