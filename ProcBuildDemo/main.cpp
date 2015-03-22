// OpenGL related includes
#include <GL\glew.h>
#include <GL\freeglut.h>

// IO includes
#include <iostream>

// Shaders related includes
#include "Shader_Loader.h"
#include "GameModels.h"

// Defines
#define uchar unsigned char

Models::GameModels* gameModels;
GLuint program_red_triangle;
GLuint program_green_triangle;

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glBindVertexArray(gameModels->getModel("triangle1"));
    glUseProgram(program_green_triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(program_red_triangle);
    glDrawArrays(GL_POINTS, 0, 3);

    glutSwapBuffers();
}

void simpleRenderScene()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLoadIdentity();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(-0.25, 0.25, 0.0);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(-0.25, -0.25, 0.0);
    glEnd();

    glTranslatef(0.0, 0.0, -4.5);
    glColor3f(0.8, 0.2, 0.1);
    glScalef(1.0, 1.0, 1.0);
    glutSolidTeapot(1.0);

    glFlush();
}

void reshapeCallback(int x, int y)
{
    if (x == 0 || y == 0) return;

    // Set new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Angle of view: 40 degrees
    // Near clipping plane: 0.5
    // Far clipping plane: 20.0

    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glViewport(0, 0, x, y);
}

void keyboardEventHandler(uchar key, int x, int y)
{
    std::cout << key << std::endl;
}

void closeCallback()
{
    std::cout << "GLUT: window closed !" << std::endl;
    glutLeaveMainLoop();
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    gameModels = new Models::GameModels();
    gameModels->createTriangleModel("triangle1");

    // Load and compile shaders
    Shader_Loader shaderLoader;
    program_red_triangle = shaderLoader.createProgram("Vertex_Shader.glsl", "Fragment_Shader_Red.glsl");
    program_green_triangle = shaderLoader.createProgram("Vertex_Shader.glsl", "Fragment_Shader_Green.glsl");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(10.0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(500, 500);
    glutInitWindowSize(800, 600);
    glutCreateWindow("My First OpenGL Window");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glewInit();
    init();

    // Register callbacks
    glutDisplayFunc(simpleRenderScene);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardEventHandler);
    glutCloseFunc(closeCallback);

    glutMainLoop();

    delete gameModels;
    glDeleteProgram(program_red_triangle);
    glDeleteProgram(program_green_triangle);
    return 0;
}