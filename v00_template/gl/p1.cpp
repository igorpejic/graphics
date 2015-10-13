#include <stdlib.h>
#include <GL/glut.h>
#include "readpoints.h"

std::vector<Point> points;

void initRendering() 
{
    glEnable(GL_DEPTH_TEST);
}

void changeSize(int w, int h) 
{
    if(h == 0) { h = 1;}

    float ratio = 1.0* w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    //gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector
}
void drawAxis(float size)
{
    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);
    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);
    
    glColor3f(1, 1, 1); // restore color
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;

void drawScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
    glLoadIdentity(); // resetiranje

    glBegin(GL_QUADS);
    //Trapezoid
    glVertex3f(points[0].x, points[0].y, 0.0f);
    glVertex3f(points[1].x, points[1].y, 0.0f);
    glVertex3f(points[2].x, points[2].y, 0.0f);
    glVertex3f(points[3].x, points[3].y, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    //Pentagon
    glVertex3f(points[4].x, points[4].y, 0.0f);
    glVertex3f(points[5].x, points[5].y, 0.0f);
    glVertex3f(points[6].x, points[6].y, 0.0f);

    glVertex3f(points[7].x, points[7].y, 0.0f);
    glVertex3f(points[8].x, points[8].y, 0.0f);
    glVertex3f(points[9].x, points[9].y, 0.0f);

    glVertex3f(points[10].x, points[10].y, 0.0f);
    glVertex3f(points[11].x, points[11].y, 0.0f);
    glVertex3f(points[12].x, points[12].y, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    //Triangle
    glVertex3f(points[13].x, points[13].y, 0.0f);
    glVertex3f(points[14].x, points[14].y, 0.0f);
    glVertex3f(points[15].x, points[15].y, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void update(int value) 
{
    _angle += 2.0f;
    if (_angle > 360) { _angle -= 360; }
    glutPostRedisplay(); // treba reci GLUT-u da se promijenio prikazTell GLUT that the display has changed
    //update glut-a nakon 25 ms
    glutTimerFunc(25, update, 0);
}



int main(int argc, char **argv) 
{
    points = readPoints();

    //for(const auto& item : points)
    //    std::cout<<item.x<<" : "<<item.y<<std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    glutCreateWindow("v0 - p1");
    glutReshapeFunc(changeSize);
    glutDisplayFunc(drawScene);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
