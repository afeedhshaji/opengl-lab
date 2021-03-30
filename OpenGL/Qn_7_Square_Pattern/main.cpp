#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

#include "../constants.hpp"

using namespace std;

void initFn()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear frame buffer to the set color
    glLoadIdentity();             // Reset co-ordinate system
}

void drawPattern(vector<pair<GLfloat, GLfloat>> points, int level)
{
    if (level == 0)
    {
        return;
    }
    // points[0], points[1] -> first quadrant
    // points[2], points[3] -> second quadrant

    pair<GLfloat, GLfloat> top_mid = make_pair((points[1].first + points[0].first) / 2, points[0].second);
    pair<GLfloat, GLfloat> bottom_mid = make_pair((points[1].first + points[0].first) / 2, points[2].second);
    pair<GLfloat, GLfloat> left_mid = make_pair(points[0].first, (points[0].second + points[3].second) / 2);
    pair<GLfloat, GLfloat> right_mid = make_pair(points[1].first, (points[1].second + points[2].second) / 2);

    pair<GLfloat, GLfloat> center = make_pair(top_mid.first, (top_mid.second + bottom_mid.second) / 2);

    // Vertical line
    glBegin(GL_LINE_LOOP);
    glVertex2f(top_mid.first, top_mid.second);
    glVertex2f(bottom_mid.first, bottom_mid.second);
    glEnd();

    // Horizontal line
    glBegin(GL_LINE_LOOP);
    glVertex2f(left_mid.first, left_mid.second);
    glVertex2f(right_mid.first, right_mid.second);
    glEnd();

    //Divide and Conquer
    vector<pair<GLfloat, GLfloat>> points_lh = {left_mid, center, bottom_mid, points[3]};
    drawPattern(points_lh, level - 1);

    vector<pair<GLfloat, GLfloat>> points_rh = {top_mid, points[1], right_mid, center};
    drawPattern(points_rh, level - 1);
}

void renderFn()
{
    // Initialize the boundaries of outer square
    vector<pair<GLfloat, GLfloat>> points = {{-0.9, 0.9}, {0.9, 0.9}, {0.9, -0.9}, {-0.9, -0.9}};

    // Draw outer square
    glBegin(GL_LINE_LOOP);
    glVertex2f(points[0].first, points[0].second);
    glVertex2f(points[1].first, points[1].second);
    glVertex2f(points[2].first, points[2].second);
    glVertex2f(points[3].first, points[3].second);
    glVertex2f(points[0].first, points[0].second);
    glEnd();

    drawPattern(points, LEVEL);

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

    initFn();

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
