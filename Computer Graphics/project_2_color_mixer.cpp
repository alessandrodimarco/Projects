//
// Alessandro DiMarco
// Project 2: Color Mixer
// 7/27/15
//

#include <GLUT/glut.h>
#include <string>

class SliderBox {
public:
    int x, y;
    float color;
    const int width = 40, height = 20;
    bool active = false;

    SliderBox(int incoming_x, int incoming_y) {
        x = incoming_x;
        y = incoming_y;
    }

    /*
     * This function will be called inside the display method
     * and will create the slider box. If the box is active
     * then the color of the box will be set to its RGB value
     * else the box will be gray.
     *
     * @param c will place the color value in the appropriate location
     *          depending on whether the box is RED, GREEN, or BLUE.
     */
    void display(char c) {
        color = (y - 90.0) / 300.0;

        if (active)
            switch (c) {
                case 'r':
                    glColor3f(color, 0, 0); break;
                case 'g':
                    glColor3f(0, color, 0); break;
                case 'b':
                    glColor3f(0, 0, color); break;
            }
        else
            glColor3f(0.5, 0.5, 0.5);

        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x, y + height);
        glVertex2i(x + width, y + height);
        glVertex2i(x + width, y);
        glEnd();
    }
};

const int WIDTH_OF_WINDOW  = 600, HEIGHT_OF_WINDOW = 500;
const int BOTTOM_OF_SLIDER = 100, TOP_OF_SLIDER    = 400;

//Two arrays for the RGB colors of the left and right sides of the rectangle.
float leftRGB[] = {0.5, 0.5, 0.5}, rightRGB[] = {0.5, 0.5, 0.5};

//This array will store the RGB values of a pixels color.
float pixelReadIn[3];

SliderBox box1( 60, 240);
SliderBox box2(140, 240);
SliderBox box3(220, 240);

/*
 * This function will convert the RGB value from a float to a
 * integer to a string and then print out each character in the
 * number above the slider bar.
 *
 * @param c   - incoming color to be converted to string
 * @param pos - places glRasterPos2i at the correct x location
 */
void printRGBvalue (float c, int pos) {
    std::string color = std::to_string((int)(c * 255));

    for (int i = 0; i < color.length(); i++) {
        glRasterPos2i(pos += 10, TOP_OF_SLIDER + 20);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, color.at(i));
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    //dsiplay the slider bars
    glBegin(GL_LINES);
    glVertex2i( 80, BOTTOM_OF_SLIDER);
    glVertex2i( 80, TOP_OF_SLIDER);
    glVertex2i(160, BOTTOM_OF_SLIDER);
    glVertex2i(160, TOP_OF_SLIDER);
    glVertex2i(240, BOTTOM_OF_SLIDER);
    glVertex2i(240, TOP_OF_SLIDER);
    glEnd();

    //print the letters R, G, and B below the slider bars
    glRasterPos2i( 73, BOTTOM_OF_SLIDER - 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    glRasterPos2i(153, BOTTOM_OF_SLIDER - 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');
    glRasterPos2i(233, BOTTOM_OF_SLIDER - 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');

    //display each slider box
    box1.display('r');
    box2.display('g');
    box3.display('b');

    //print the RGB values above the slider bars
    glColor3f(1, 1, 1);
    printRGBvalue (box1.color,  60);
    printRGBvalue (box2.color, 140);
    printRGBvalue (box3.color, 220);

    //dsiplay the color square
    glBegin(GL_QUADS);
    glColor3f(box1.color, box2.color, box3.color);
    glVertex2i(320, 200);
    glVertex2i(320, 400);
    glVertex2i(520, 400);
    glVertex2i(520, 200);

    //dsiplay the rectangle
    glColor3fv(leftRGB);
    glVertex2i(320, 100);
    glVertex2i(320, 175);
    glColor3fv(rightRGB);
    glVertex2i(520, 175);
    glVertex2i(520, 100);
    glEnd();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key){
        case 'l':
            leftRGB[0] = box1.color;
            leftRGB[1] = box2.color;
            leftRGB[2] = box3.color;
            break;

        case 'r':
            rightRGB[0] = box1.color;
            rightRGB[1] = box2.color;
            rightRGB[2] = box3.color;
            break;
    }
    glutPostRedisplay();
}

/*
 * This function checks to see if the mouse click or motion
 * is within the slider box gravity.
 *
 * @param x       - coordinate x of mouse position
 * @param box     - the slider box to be checked
 * @param gravity - will set the amount from the left and right of the box the user may click/move
 * @return the truth value depending on whether the mouse click is inside/near the box
 */
bool check_x_range(int x, SliderBox box, int gravity) {
    return (x > box.x - gravity && x < box.x + box.width + gravity);
}

/*
 * This function is used in the mouse function and will
 * check where the mouse is and set the y coordinate of the box
 * accordingly.
 *
 * @param x   - incoming mouse position of coordinate x
 * @param y   - incoming mouse position of coordinate y
 * @param box - reference of the slider box to be worked on
 */
void set_box_y_value(int x, int y, SliderBox &box) {
    //If the mouse click is INSIDE the slider box then this prevents it from moving slightly.
    if (x > box.x && x < box.x + box.width && y > box.y && y < box.y + box.height) {
        box.active = true;
        return;
    }

    //If the mouse click is in the area WITHIN the slider bar then set the slider box to that position.
    else if (y >= BOTTOM_OF_SLIDER && y <= TOP_OF_SLIDER) {
        box.y = y - box.height/2;
        box.active = true;
    }

    //If the mouse click is at the TOP of the bar or around it, then set the slider box to the top of the bar.
    else if (y >= TOP_OF_SLIDER && y < TOP_OF_SLIDER + 7) {
        box.y = TOP_OF_SLIDER - box.height/2;
        box.active = true;
    }

    //If the mouse click is at the BOTTOM of the bar or around it, then set the slider box to the bottom of the bar.
    else if (y >= BOTTOM_OF_SLIDER - 7 && y <= BOTTOM_OF_SLIDER) {
        box.y = BOTTOM_OF_SLIDER - box.height/2;
        box.active = true;
    }
}

/*
 * When the left button of the mouse is down then the first condition to check is
 * if the mouse lies within one of the slider bars or if the mouse lies in the
 * rectangle. If the mouse position is in the slider bar then set the y
 * coordinate of the slider box. If the mouse position lies in the rectangle
 * then set the color of the rectangle to that pixels color.
 */
void mouse(int button, int state, int x, int y) {
    y = HEIGHT_OF_WINDOW - y - 1;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if      (check_x_range(x, box1, 4)) set_box_y_value(x, y, box1);
        else if (check_x_range(x, box2, 4)) set_box_y_value(x, y, box2);
        else if (check_x_range(x, box3, 4)) set_box_y_value(x, y, box3);

        else if (x >= 320 && x <= 520 && y >= 100 && y <= 175) {
            glutSwapBuffers();
            glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelReadIn);
            box1.y = (300 * pixelReadIn[0]) + 90;
            box2.y = (300 * pixelReadIn[1]) + 90;
            box3.y = (300 * pixelReadIn[2]) + 90;
        }
        glutPostRedisplay();
    } else {
        box1.active = false;
        box2.active = false;
        box3.active = false;
        glutPostRedisplay();
    }
}

/*
 * This function is used in the motion function and will
 * check where the mouse is and set the y coordinate of the box
 * accordingly.
 *
 * @param y   - incoming mouse position of coordinate y
 * @param box - reference of the slider box to be worked on
 */
void set_box_y_value(int y, SliderBox &box) {
    //If the motion of the mouse is WITHIN the slider bar then set the slider box to it.
    if (y >= BOTTOM_OF_SLIDER && y <= TOP_OF_SLIDER)
        box.y = y - box.height/2;

    //If the motion of the mouse passes the TOP of the silde bar then set the slider box to the top.
    else if (y > TOP_OF_SLIDER && y < TOP_OF_SLIDER + 50)
        box.y = TOP_OF_SLIDER - box.height/2;

    //If the motion of the mouse passes the BOTTOM of the slide bar then set the slider box to the bottom.
    else if (y > BOTTOM_OF_SLIDER - 50 && y < BOTTOM_OF_SLIDER)
        box.y = BOTTOM_OF_SLIDER - box.height/2;
}

/*
 * If the mouse is in motion then the first condition to check is if it lies
 * within one of the slider boxes. Then check if that box was active and if
 * both conditions are true then set the y value for that slider box.
 */
void motion(int x, int y) {
    y = HEIGHT_OF_WINDOW - y - 1;

    if      (check_x_range(x, box1, 40) && box1.active) set_box_y_value(y, box1);
    else if (check_x_range(x, box2, 40) && box2.active) set_box_y_value(y, box2);
    else if (check_x_range(x, box3, 40) && box3.active) set_box_y_value(y, box3);
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Project 2: Color Mixer");
    glClearColor(0.75, 0.75, 0.75, 0.0);
    gluOrtho2D(0, WIDTH_OF_WINDOW, 0, HEIGHT_OF_WINDOW);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
}
