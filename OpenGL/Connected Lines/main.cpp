#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

// Global Variables
vector<pair<GLfloat, GLfloat>> Points;
char input_filename[] = "input.txt";

void readInput(char *filename)
{
    GLfloat a, b;
    ifstream input(filename);
    while (input >> a >> b)
    {
        Points.push_back(make_pair(a, b));
        Points.push_back(make_pair(a, b));
    };

    // Remove the beginning and end
    if (Points.size() > 0)
    {
        Points.erase(Points.begin());
    }
    if (Points.size() > 0)
    {
        Points.pop_back();
    }
    input.close();
}

void initFn()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear frame buffer to the set color
    glLoadIdentity();             // Reset co-ordinate system
}

void renderFn()
{
    /* Plot points*/
    glBegin(GL_LINES);
    for (auto it : Points)
    {
        glVertex2f(it.first, it.second);
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
    glutInitWindowSize(400, 300);     // Specify window size
    glutInitWindowPosition(100, 100); // Specify window position
    glutCreateWindow("Question 3");   // Use the window name here

    readInput(input_filename);

    initFn();

    /* Display Callback function.
    Takes in a function pointer as argument. */
    glutDisplayFunc(renderFn);

    /* Program Execution loop */
    glutMainLoop();

    return 0;
}
