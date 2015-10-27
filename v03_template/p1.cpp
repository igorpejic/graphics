#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

long binomials(long n, long k)
{
    // n && k >=0
    long i;
    long b;
    if (0 == k || n == k) {
        return 1;
    }
    if (k > n) {
        return 0;
    }
    if (k > (n - k)) {
        k = n - k;
    }
    if (1 == k) {
        return n;
    }
    b = 1;
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
        if (b < 0) return -1; /* ERR!!!! OVERFLOW */
        b /= i;
    }
    return b;
}

void changeSize(int w, int h)
{
    if(h == 0) {
        h = 1;
    }

    float ratio = 1.0* w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
}


Vector4d pt_x, pt_y;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // idemo u model space
    glLoadIdentity(); // resetiranje

    gluLookAt(0.0,0.0,5.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector

    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(pt_x(0), pt_y(0), 0.0f);
    glVertex3f(pt_x(1), pt_y(1), 0.0f);
    glVertex3f(pt_x(2), pt_y(2), 0.0f);
    glVertex3f(pt_x(3), pt_y(3), 0.0f);
    glEnd();

    
    glutSwapBuffers();
}
void update(int /*value*/)
{
    glutPostRedisplay();
    //update glut-a nakon 25 ms
    glutTimerFunc(25, update, 0);
}


int main(int argc, char **argv)
{
    pt_x << -0.95, -0.25, 0.6, 0.95;
    pt_y << -0.5, 0.8, 0.6, -0.5;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    glutCreateWindow("v3 - p1");
    glutReshapeFunc(changeSize);
    glutDisplayFunc(drawScene);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
