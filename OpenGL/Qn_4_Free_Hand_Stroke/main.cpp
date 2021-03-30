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
vector<pair<int, int>> Points;
int cnt = 0;
char input_filename[] = "input.txt";
int mouse_1_down = 0;
double w;
double h;

void initFn()
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
}

void mouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouse_1_down = 1;
        }
        else if (state == GLUT_UP)
        {
            mouse_1_down = 0;
            Points.clear();
        }
    }
}

void motion(int mx, int my)
{
    if (mouse_1_down == 1)
    {
        GLint x = mx;
        GLint y = my; // screenheight is fixed
        Points.push_back(std::make_pair(x, y));

        glLineWidth(3.0f); // stroke width

        glBegin(GL_LINE_STRIP);
        for (auto point : Points)
        {
            glVertex2f(point.first, point.second);
        }
        glEnd();
        glFlush();
    }
}

void renderFn()
{
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
    glutCreateWindow(TITLENAME);

    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    initFn();

    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
