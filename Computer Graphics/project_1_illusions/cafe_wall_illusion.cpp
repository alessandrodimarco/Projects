#include <iostream>
#include <math.h>
#include <GLUT/glut.h>

const int width = 625;
const int height = 375;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);

    int x = 10;
    int y = 10;
    const int squareSize = 50;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 600; j += 100) {
            glColor3f(0.0, 0.0, 0.0);
            //bottom left
            glVertex2f(x + j, y);
            //top left
            glVertex2f(x + j, y + squareSize);
            //top right
            glVertex2f(x + squareSize + j, y + squareSize);
            //bottom right
            glVertex2f(x + squareSize + j, y);

            //create lines
            glColor3f(0.5, 0.5, 0.5);
            glVertex2f(0, y-1);
            glVertex2f(0, y+1);
            glVertex2f(width, y+1);
            glVertex2f(width, y-1);
        }
        //move squares up
        y += 51;

        //shift squares left or right
        if (i < 2 || i > 3)
            x += 25;
        else
            x -= 25;
    }

    //create top line
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(0, y-1);
    glVertex2f(0, y+1);
    glVertex2f(width, y+1);
    glVertex2f(width, y-1);

    glEnd();
    glFlush();

}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Cafe Wall illusion");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(display);
    glutMainLoop();
}
