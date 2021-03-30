#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

#include "../constants.hpp"

using namespace std;

struct Vertex
{
    GLfloat x, y, z;
};

// Global Variables
vector<Vertex> vertices;

double w;
double h;

void readInput(char *filename)
{
    GLfloat a, b, c;
    ifstream input(filename);
    while (input >> a >> b >> c)
    {
        vertices.push_back({a, b, c});
    };

    input.close();
}

void initFn()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glOrtho(0, w, h, 0, -1, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear frame buffer to the set color
    glLoadIdentity();                                   // Reset co-ordinate system
}

void renderFn()
{
    /* Plot points*/
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    for (int i = 4; i < 8; i++)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    for (int i = 8; i < 12; i++)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    /* Glut initialization */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    /* Glut window configurations */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Specify window size
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2); // Specify window position
    glutCreateWindow(TITLENAME);

    readInput(FILENAME);

    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    initFn();

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
