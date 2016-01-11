
#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/glext.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
struct Point
{
    Point(){}
    Point(float _x, float _y, float _z) :x(_x), y(_y), z(_z){}
    float x,y,z;
};

const int particleNum = 20;
double tt = 0.;
Point getPosition(const double& r, const double &t, const double& scale)
{
    return Point(r*cos(scale*t), r*cos(scale*t), scale*t);
}

void handleKeypress(unsigned char key, int x, int y) 
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    }
}

void initRendering() 
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void handleResize(int w, int h) 
{
    if(h == 0) { h = 1;}

        float ratio = 1.0* w / h;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
}

void drawParticle()
{
    glPushMatrix();
    Point p = getPosition(1, tt, 1);
    glTranslatef(p.x,p.y,p.z);
    glutSolidSphere(0.2,6,6);
    glPopMatrix();
}

void drawScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
    glLoadIdentity(); // resetiranje

    gluLookAt(0.0,0.0,5.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector

    glTranslatef(0.0f, 0.0f, -20.0f);


    drawParticle();

    glutSwapBuffers();
}

void update(int /*value*/)
{
    glutPostRedisplay();
    tt+=0.1;
    if(tt>=100){tt=100;}
    //update glut-a nakon 25 ms
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) 
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    glutCreateWindow("gl_teksture");
    initRendering();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
