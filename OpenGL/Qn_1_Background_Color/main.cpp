#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

#include "../constants.hpp"

using namespace std;

struct color
{
    GLfloat r, g, b, a;
};

// Global Variables
struct color Color;
// char input_filename[] = "input.txt";

void initFn()
{
    glClearColor(Color.r, Color.g, Color.b, Color.a);
    glClear(GL_COLOR_BUFFER_BIT); // Clear frame buffer to the set color
    glLoadIdentity();             // Reset co-ordinate system
}

void renderFn(void)
{
    glFlush();
}

void readInput(char *filename)
{
    ifstream input(filename);
    while (input >> Color.r >> Color.g >> Color.b >> Color.a)
    {
    };
    input.close();
}

int main(int argc, char **argv)
{
    /* Glut initialization */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    /* Glut window configurations */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Specify window size
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2); // Specify window position
    glutCreateWindow(TITLENAME);

    readInput(FILENAME);

    initFn();

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
