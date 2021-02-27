#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct color
{
    GLfloat r, g, b, a;
};

// Global Variables
struct color Color;
char input_filename[] = "input.txt";

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
    glutInitWindowSize(400, 300);     // Specify window size
    glutInitWindowPosition(100, 100); // Specify window position
    glutCreateWindow("Question 1");   // Use the window name here

    readInput(input_filename);

    initFn();

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
