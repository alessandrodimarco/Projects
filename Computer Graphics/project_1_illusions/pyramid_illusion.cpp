#include <iostream>
#include <math.h>
#include <GLUT/glut.h>

const int width = 600;
const int height = 600;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);

    double color = 0.01;

    for (int shift = 0; shift < 300; shift += 3) {
        glColor3f(color, color, color);

        //bottom left vertex
        glVertex2f(shift, shift);
        //top left vertex
        glVertex2f(shift, height - shift);
        //top right vertex
        glVertex2f(width - shift, height - shift);
        //bottom right vertex
        glVertex2f(width - shift, shift);

        color += 0.01;
    }
    glEnd();
    glFlush();

}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Pyramid illusion");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(display);
    glutMainLoop();
}
