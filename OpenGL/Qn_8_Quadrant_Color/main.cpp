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
int mouse_1_down = 0;
int ARG_OPT;

GLfloat w;
GLfloat h;
GLfloat colors[3] = {0.0, 0.0, 0.0};

enum QuadrantColors
{
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4
};

// To get the color based on the quadrant in which the point is in
int getColorBasedOnQuadrant(GLfloat x, GLfloat y)
{
    if (x == 0 || y == 0)
        return QuadrantColors::BLACK;

    if (x > 0)
        if (y > 0)
            return QuadrantColors::RED;
        else
            return QuadrantColors::YELLOW;
    else if (y > 0)
        return QuadrantColors::GREEN;
    else
        return QuadrantColors::BLUE;
}

// To get brightness the of the color based on the condition
// given in the question :
// Brightness = (Anglular coverage) / (Π/2)
// Angle made with the positive x-axis :
// Case 1 : 1st Quadrant => Tan^−1(y/x)
// Case 2 : 2nd Quadrant => Π/2 + Tan^−1(y/x)
// Case 3 : 3rd Quadrant => Tan^−1(y/x)
// Case 4 : 4th Quadrant => Π/2 + Tan^−1(y/x)
GLfloat getBrightness(GLfloat x, GLfloat y, int quadrant)
{
    switch (quadrant)
    {
    case 1:
        return (GLfloat)(atan(y / x) / (PI / 2));
    case 2:
        return (GLfloat)((PI / 2 + atan(y / x)) / (PI / 2));
    case 3:
        return (GLfloat)(atan(y / x) / (PI / 2));
    case 4:
        return (GLfloat)((PI / 2 + atan(y / x)) / (PI / 2));
    default:
        return 0;
    }
}

void initFn()
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
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
        }
    }
}

void motion(int mx, int my)
{
    if (mouse_1_down == 1)
    {
        GLint x = mx;
        GLint y = h - my; // screenheight is fixed

        GLfloat red, blue, green, yellow;

        glLineWidth(3.0f); // stroke width

        // Get color based on quadrant and arg options
        int color = getColorBasedOnQuadrant(x - (w / 2), y - (h / 2));

        // Alternate color combination
        if (ARG_OPT == 2)
        {
            switch (color)
            {
            case QuadrantColors::RED:
                red = getBrightness(x - (w / 2), y - (h / 2), 1);

                colors[0] = red;
                colors[1] = red;
                colors[2] = 0.0;

                break;

            case QuadrantColors::GREEN:
                green = getBrightness(x - (w / 2), y - (h / 2), 2);

                colors[0] = 0.0;
                colors[1] = green;
                colors[2] = green;

                break;

            case QuadrantColors::BLUE:

                blue = getBrightness(x - (w / 2), y - (h / 2), 3);

                colors[0] = 0.0;
                colors[1] = blue;
                colors[2] = 0.0;

                break;

            case QuadrantColors::YELLOW:

                yellow = getBrightness(x - (w / 2), y - (h / 2), 4);

                colors[0] = yellow;
                colors[1] = 0.0;
                colors[2] = yellow;

                break;

            default:
                colors[0] = 0.0;
                colors[1] = 0.0;
                colors[2] = 0.0;

                break;
            };
        }
        // Original color combination
        else
        {
            switch (color)
            {
            case QuadrantColors::RED:
                red = getBrightness(x - (w / 2), y - (h / 2), 1);

                colors[0] = red;
                colors[1] = 0.0;
                colors[2] = 0.0;

                break;

            case QuadrantColors::GREEN:
                green = getBrightness(x - (w / 2), y - (h / 2), 2);

                colors[0] = 0.0;
                colors[1] = green;
                colors[2] = 0.0;

                break;

            case QuadrantColors::BLUE:

                blue = getBrightness(x - (w / 2), y - (h / 2), 3);

                colors[0] = 0.0;
                colors[1] = 0.0;
                colors[2] = blue;

                break;

            case QuadrantColors::YELLOW:

                yellow = getBrightness(x - (w / 2), y - (h / 2), 4);

                colors[0] = yellow;
                colors[1] = yellow;
                colors[2] = 0.0;

                break;

            default:
                colors[0] = 0.0;
                colors[1] = 0.0;
                colors[2] = 0.0;

                break;
            };
        }

        glColor3f(colors[0], colors[1], colors[2]);

        glBegin(GL_LINE_STRIP);
        glVertex2f(w / 2, h / 2);
        glVertex2f(x, y);
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
    if (argc >= 2)
    {
        ARG_OPT = stoi(argv[1]);
        // cout << ARG_OPT;
    }

    /* Glut initialization */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    /* Glut window configurations */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Specify window size
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2); // Specify window position
    glutCreateWindow(TITLENAME);                                               // Use the window name here

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
