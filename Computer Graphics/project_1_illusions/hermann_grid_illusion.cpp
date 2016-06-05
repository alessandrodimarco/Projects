#include <iostream>
#include <math.h>
#include <GLUT/glut.h>

const int width = 525;
const int height = 525;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);

    //starting point for bottom left vertex of black square
    int x = 25;
    int y = 25;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 500; j += 100) {
            //bottom left vertex
            glVertex2f(x + j, y);
            //top left vertex
            glVertex2f(x + j, y + 75);
            //top right vertex
            glVertex2f(x + 75 + j, y + 75);
            //bottom right vertex
            glVertex2f(x + 75 + j, y);
        }
        //move vertex vertically 100 units
        y += 100;
    }
    glEnd();
    glFlush();

}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Hermann Grid illusion");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(display);
    glutMainLoop();
}
