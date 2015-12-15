#include <GL/gl.h>

#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;
using std::vector;

struct Point
{
 Point(float _x, float _y, float _z){x=_x; y=_y; z=_z;}
 float x, y, z;
};

vector <Point> pts;

Point calcNormal(Point p1, Point p2, Point p3){
//v1 = t2 - t1
//v2 = t3 - t1

//vx = v1y * v2z - v1z * v2y
//vy = v1z * v2x - v1x * v2z
//vz = v1x * v2y - v1y * v2x
	float vx, vy, vz;
	vx = p2.x-p1.x;
	vy = p2.y-p1.y;
	vz = p2.z-p1.z;
	Point v1(vx, vy, vz);

	vx = p3.x-p1.x;
	vy = p3.y-p1.y;
	vz = p3.z-p1.z;

	// normala u drugi smjer
	//Point v2(-vx, -vy, -vz);

	Point v2(vx, vy, vz);

	vx = v1.y * v2.z - v1.z * v2.y;
	vy = v1.z * v2.x - v1.x * v2.z;
	vz = v1.x * v2.y - v1.y * v2.x;
	float I = sqrt(vx*vx+ vy*vy+ vz*vz);
	vx /= I;
	vy /= I;
	vz /= I;
	return Point(vx, vy, vz);
}

// pretpostavka da vektor ima hvatiste u (0,0,0)
void drawNormal(float p0[3], float p1[3] )
{
    const float size=1.;
    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(p0[0],p0[1],p0[2]);
        glVertex3f(p1[0],p1[1],p1[2]);
    glEnd();
    glLineWidth(1);

    glColor3f(1, 1, 1); // restore color
}

void drawScene()
{
    glClearColor(0.9f, 0.92f, 0.94f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_FLAT/*GL_SMOOTH*/);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    float p0[3]={0,0,0};
    float p1[3]={1,1,1};
    drawNormal(p0,p1);

	glRotatef(35, 1, 0, 0);
    glBegin(GL_TRIANGLES);
    for(int i=0; i < 3; ++i)
    {
	glVertex3f(pts[i].x, pts[i].y, pts[i].z);
    }
	float vx, vy, vz;

    Point normal = calcNormal(pts[0], pts[1], pts[2]);
    glEnd();
    float n0[3]={0.5,0.2,0};
    float n1[3] = {normal.x, normal.y, normal.z};
    drawNormal(n0, n1);

    glutSwapBuffers();
    glutPostRedisplay();
}



void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    }
}
void handleResize(int w, int h)
{
    /*glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);*/

    if (h == 0) { h = 1; }
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector
}

void initRendering()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT,GL_DIFFUSE);

    float black[4]={0,0,0,0};

    glMaterialfv(GL_FRONT,GL_AMBIENT,black);
    glMaterialfv(GL_FRONT,GL_SPECULAR,black);
    glEnable(GL_CULL_FACE);
}

int main(int argc, char** argv)
{
    pts.push_back(Point(0,0,0));
    pts.push_back(Point(1,0,0));
    pts.push_back(Point(1,1,0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    //Create the window
    glutCreateWindow("normale...");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutMainLoop();
    return 0;
}

