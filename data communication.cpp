#include <GL/glut.h>
#include <math.h>

float packetX = -0.8;   // Initial packet position

void drawRectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 100; i++)
    {
        float theta = 2 * 3.1416 * i / 100;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawText(float x, float y, const char *string)
{
    glRasterPos2f(x, y);
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sender
    glColor3f(0.2, 0.2, 1);
    drawRectangle(-0.9, -0.3, -0.7, 0.3);
    glColor3f(0, 0, 0);
    drawText(-0.88, 0.32, "Sender");

    // Receiver
    glColor3f(0.2, 1, 0.2);
    drawRectangle(0.7, -0.3, 0.9, 0.3);
    glColor3f(0, 0, 0);
    drawText(0.72, 0.32, "Receiver");

    // Internet Cloud
    glColor3f(1, 1, 0);
    drawCircle(0, 0, 0.3);
    glColor3f(0, 0, 0);
    drawText(-0.08, 0.32, "Internet");

    // Moving packet
    glColor3f(1, 0, 0);
    drawRectangle(packetX, -0.05, packetX + 0.1, 0.05);

    glutSwapBuffers();
}

void timer(int)
{
    packetX += 0.01;

    if(packetX > 0.9)
        packetX = -0.8;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Data Communication Over Internet - OpenGL");

    glClearColor(1, 1, 1, 1);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
}
