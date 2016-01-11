
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
Point getPosition(const double& r, const double &t, const double& scale, const double& w, const double& phase = M_PI/2)
{
    return Point(r*(1 + 0.1*scale*t)*cos(scale*w*t + phase), 
			     r*(1 + 0.1*scale*t)*sin(scale*w*t + phase), 
				                                   scale*t);
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

void draw_sphere(double radius, int lats, int longs)
{
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i-1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

void drawParticle(Point p)
{
    glPushMatrix();
    glTranslatef(p.x,p.y,p.z);
	glutSolidSphere(0.5, 6, 6); 
    glPopMatrix();
}

void draw_particles()
{
	int i;
	for (i = 1; i <= 50; i++) {
		glColor3f(i/50.0f, 0.5f, 0.5f);
		Point tmp = getPosition(0.1*i, tt/2, 0.05*i, 1);
		drawParticle(tmp);
	}
}

void drawScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
    glLoadIdentity(); // resetiranje

    gluLookAt(0.0,0.0,-5.0, // camera
              0.0,0.0,+1.0, // where
              0.0f,1.0f,0.0f); // up vector

    glTranslatef(0.0f, 0.0f, +20.0f);


    draw_particles();

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
