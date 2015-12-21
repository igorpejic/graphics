
#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/glext.h>
#include <vector>
#include <array>
#include <iostream>
using namespace std;
struct Point
{
    Point(){}
    Point(float _x, float _y, float _z) :x(_x), y(_y), z(_z){}
    float x,y,z;
};

vector<Point> points;

vector<float> attributes;

struct Cell
{
    array<int, 4> ids;
};
vector<Cell> cells;

struct Case {
 unsigned int c : 4;
};

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

void drawBox()
{
    glBegin(GL_QUADS);
    for(auto c: cells)
    {
        for(int i=0; i<4; ++i)
        { glVertex3f(points[c.ids[i]].x, points[c.ids[i]].y,points[c.ids[i]].z); }
    }
    glEnd();

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

    drawBox();

    glutSwapBuffers();
}

void initMesh()
{
    float dx = 1;
    float dy = 1;
    for(int j=0; j<5; ++j)
    {
        for(int i=0; i<5; ++i)
        {
            points.push_back(Point(i*dx,j*dy,0));

        }
    }
    attributes = {1,2,3,4,7,
                 2,7,8,6,2,
                 3,7,9,7,3,
                 1,3,6,6,3,
                 0,1,1,3,2};
    for(int i=0; i<25; ++i)
    {points[i].z = attributes[i];}

    int szx=5;
    int szy=5;
    for(int j=0; j<4; ++j)
    {
        for(int i=0; i<4; ++i)
        {
            Cell c;
            c.ids = {j*szx+i, j*szx+i+1, (j+1)*szx+i+1, (j+1)*szx+i};
            cells.push_back(c);
        }
    }

    for(auto c: cells)
    {
        std::cout << c << 'c';
    }
}

int main(int argc, char** argv) 
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    initMesh();
    glutCreateWindow("gl_teksture");
    initRendering();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutMainLoop();
    return 0;
}
