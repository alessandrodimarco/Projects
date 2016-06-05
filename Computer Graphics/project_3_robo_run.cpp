//
// Alessandro DiMarco
// Project 3
// 8/6/15
//

#include <GLUT/glut.h>
#include <iostream>
#include <math.h>

GLfloat light_pos[] = {2, 4, 4, 1};
GLfloat       spe[] = {0.25, 0.25, 0.25, 1.0};
GLfloat       amb[] = {0.3, 0.3, 0.3, 1.0};

GLfloat robotColor[] = {0.6, 0.6, 0.6},
red[]   = {1, 0, 0, 1},
orange[]   = {1, 0.5, 0, 1},
green[] = {0, 1, 0, 1},
blue[]  = {0, 0.2, 0.8, 1},
black[] = {0, 0, 0, 1};

GLfloat theta = 0, dt  = 1;

int zoom           = 120;
int resolution     = 40;
double bounceShift = 0;

const int WIDTH_OF_WINDOW = 600, HEIGHT_OF_WINDOW = 600;
const float DEG2RAD = 3.14159/180;
bool pause   = false;
bool bounce  = true;
bool forward = true;
bool falling = true;

double spherePos[6][3]     = {{-6, 15, -9.5}, {-4, 20, -5.5}, {0, 17, -4}, {4, 18, -5.5}, {6, 19, -9.5}, {0, 25, -10.5}};
std::string instructions[] = {"Welcome to ROBO  RU N", "Avoid the green  sp heres"};
double stringPos[][2]      = {{-15, 14}, {-15, 12}};

int instructionsIndex = 0;
int posIndex = 0;
int counter  = 0;
bool moving  = false;

void printString () {

    for (int i = 0; i < instructions[instructionsIndex].length(); i++) {
        glRasterPos3i(stringPos[posIndex][0] += 0.95, stringPos[posIndex][1], -10);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instructions[instructionsIndex].at(i));
    }

    stringPos[0][0] = -15;
    stringPos[1][0] = -15;
}

void drawCircles(double radius) {
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);

    //draw 6 circles around the ring for the spheres to fall into
    for (int j = 0; j <= 5; j++) {
        glPushMatrix();
        if (j == 5) glTranslated(spherePos[j][0], 1, spherePos[j][2]);
        else glTranslated(spherePos[j][0], 0, spherePos[j][2]);

        glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++) {
            float degInRad = i*DEG2RAD;
            glVertex3f(cos(degInRad)*radius, -2.95, sin(degInRad)*radius);
        }
        glEnd();
        glPopMatrix();
    }
}

void drawSpheres() {
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);

    //draw 6 spheres around the circles on the ring
    for (int j = 0; j < 6; j++) {
        glPushMatrix();
        glTranslated(spherePos[j][0], spherePos[j][1], spherePos[j][2]);
        gluSphere(quadObj, 0.75, resolution, resolution);
        glPopMatrix();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 2, 30);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    //create torus in background
    glPushMatrix();
    glTranslated(0, 8, -30);
    glutSolidTorus(0.9, 4, 48, 96);
    glPopMatrix();

    //create ring around torus in background
    glPushMatrix();
    glRotated(theta-180, 0, 8, -30);
    glTranslated(3.7, 8, -29.2);
    glRotated(90, 1, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    gluCylinder(quadObj, 1.2, 1.2, 1, resolution, resolution);
    glPopMatrix();

    //center cone
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
    glTranslated(0, -2, -10);
    glRotated(90, 1, 0, 0);
    gluCylinder(quadObj, 0, 2.5, 1, resolution, resolution);
    glPopMatrix();

    //floor
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    gluQuadricOrientation(quadObj, GLU_INSIDE);
    glPushMatrix();
    glTranslated(0, -3, -10);
    glRotated(90, 1, 0, 0);
    gluDisk(quadObj, 2, 8, 50, 50);
    glPopMatrix();

    //bottom cylinder
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    gluQuadricOrientation(quadObj, GLU_OUTSIDE);
    glPushMatrix();
    glTranslated(0, -3, -10);
    glRotated(90, 1, 0, 0);
    gluCylinder(quadObj, 8, 8, 5, resolution, resolution);
    glPopMatrix();

    drawSpheres();
    drawCircles(1);

    //print instructions
    if (counter < 400) {
        printString();
        if (counter == 200) {
            instructionsIndex++;
            posIndex++;
        }
        counter++;
    }

    //move robot and change orientation
    if (forward) {
        glTranslated(0, 0, -10);
        glRotated(theta, 0, 1, 0);
        glTranslated(-6, 0, 0);
    }
    else {
        glTranslated(0, 0, -10);
        glRotated(theta-180, 0, 1, 0);
        glTranslated(6, 0, 0);

    }

    //bouncing
    glTranslated(0, bounceShift, 0);

    //head
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, robotColor);
    glPushMatrix();
    glTranslated(0, 0.65, 0);
    gluSphere(quadObj, 0.85, 30, 30);
    glPopMatrix();

    //body
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    gluCylinder(quadObj, 0.75, 0.45, 2, resolution, resolution);

    //left arm
    glPushMatrix();
    glTranslated(0.5, 0, 0);
    gluCylinder(quadObj, 0.2, 0.2, 1.5, resolution, resolution);
    glPopMatrix();

    //right arm
    glPushMatrix();
    glTranslated(-0.5, 0, 0);
    gluCylinder(quadObj, 0.2, 0.2, 1.5, resolution, resolution);
    glPopMatrix();

    //feet
    glTranslated(0, 0, 2);
    gluCylinder(quadObj, 0.45, 0.1, 0.3, resolution, resolution);
    glPopMatrix();

    //left eye
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glPushMatrix();
    glTranslated(-0.3, 0.95, 0.7);
    gluSphere(quadObj, 0.1, resolution, resolution);
    glPopMatrix();

    //right eye
    glPushMatrix();
    glTranslated(0.3, 0.95, 0.7);
    gluSphere(quadObj, 0.1, resolution, resolution);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void idle(void) {

    if (!pause) {
        //make spheres start at random heights and have them fall
        for (int j = 0; j < 6; j++)
            (spherePos[j][1] < -5) ? spherePos[j][1] = (rand() % 15) + 15: spherePos[j][1] -= 0.1;

        //make robot bounce up and down
        if (bounce)
            (bounceShift > 1) ? bounce = false: bounceShift += 0.04;
        else
            (bounceShift < -0.5) ? bounce = true: bounceShift -= 0.04;

        //move robot and ring in the background
        if (moving) {
            if (forward)
                theta += dt;
            else
                theta -= dt;
        }
    }

    glutPostRedisplay();
}

void keyboard (int key, int x, int y) {
    if (GLUT_KEY_DOWN && !pause) {
        switch (key) {
            //use left and right keys to move the robot
            case GLUT_KEY_RIGHT:
                forward = true;
                theta += dt;
                moving = true;
                break;

            case GLUT_KEY_LEFT:
                forward = false;
                theta -= dt;
                moving = true;
                break;

            //zoom in and out using up and down keys
            case GLUT_KEY_UP:
                zoom -= (zoom >= 100) ? 5: 0;
                break;

            case GLUT_KEY_DOWN:
                zoom += (zoom <= 125) ? 5: 0;
                break;
        }
    }

    //if space bar is pressed then the game will pause
    if (GLUT_KEY_DOWN && key == ' ') {
        (pause) ? pause = false: pause = true;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    std::cout << "space bar -> pause \n";
    std::cout << "left  key -> move clockwise \n";
    std::cout << "right key -> move counter clockwise \n";
    std::cout << "up    key -> zoom in \n";
    std::cout << "down  key -> zoom out \n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Project 3");

    glClearColor(0.35, 0.35, 0.35, 0);
    glEnable(GL_DEPTH_TEST);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
}
