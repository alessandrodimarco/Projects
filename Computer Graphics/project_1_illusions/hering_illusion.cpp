#include <iostream>
#include <math.h>
#include <GLUT/glut.h>

const int width = 600;
const int height = 300;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    //create diagonal line
    int topLeftPoint  = -300;
    int bottomRightPoint = width+300;
    glVertex2f(topLeftPoint, height);
    glVertex2f(bottomRightPoint, 0);

    for (int i = 0; i < 30; i++) {
    //move diagonal line across the window and create one vertical line
        topLeftPoint  += 40;
        bottomRightPoint -= 40;
        glVertex2f(topLeftPoint, height);
        glVertex2f(bottomRightPoint, 0);
    }

    //horizontal lines
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0, 200);
    glVertex2f(600, 200);
    glVertex2f(0, 100);
    glVertex2f(600, 100);

    glEnd();
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Hering illusion");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(display);
    glutMainLoop();
}
