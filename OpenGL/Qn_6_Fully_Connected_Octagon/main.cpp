#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

#include "../constants.hpp"

using namespace std;

// Global Variables
vector<pair<GLfloat, GLfloat>> Points;
double w;
double h;

void readInput(char *filename)
{
    GLfloat a, b;
    ifstream input(filename);
    while (input >> a >> b)
    {
        Points.push_back(make_pair(a, b));
    };

    input.close();
}

void initFn()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glOrtho(0, w, h, 0, -1, 1);
    glClear(GL_COLOR_BUFFER_BIT); // Clear frame buffer to the set color
    glLoadIdentity();             // Reset co-ordinate system
}

void renderFn()
{
    /* Plot points*/
    glBegin(GL_LINES);
    for (int i = 0; i < Points.size(); i++)
    {
        for (int j = i + 1; j < Points.size(); j++)
        {
            glVertex2f(Points[i].first, Points[i].second);
            glVertex2f(Points[j].first, Points[j].second);
        }
    }
    glEnd();

    glFlush();
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
    glutCreateWindow(TITLENAME);                                               // Use the window name here

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
