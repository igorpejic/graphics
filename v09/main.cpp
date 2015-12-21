
#include <iostream>
#include <stdlib.h>
//#include <cmath>

#include <GL/glut.h>
#include <GL/glext.h>
#include <vector>
#include <array>
#include <iostream>
using namespace std;

//using std::max;
//using std::min;
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

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

const float val = 5.0f;

int n_intersections(Cell cell)
{
    int n = 0;
    float _max, _min;
    _max = max(attributes[cell.ids[0]], attributes[cell.ids[1]]);
    _min = min(attributes[cell.ids[0]], attributes[cell.ids[1]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val) n++;

    _max = max(attributes[cell.ids[1]], attributes[cell.ids[2]]);
    _min = min(attributes[cell.ids[1]], attributes[cell.ids[2]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val) n++;
    _max = max(attributes[cell.ids[2]], attributes[cell.ids[3]]);
    _min = min(attributes[cell.ids[2]], attributes[cell.ids[3]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val) n++;

    _max = max(attributes[cell.ids[0]], attributes[cell.ids[3]]);
    _min = min(attributes[cell.ids[0]], attributes[cell.ids[3]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val) n++;
    return n;
}

Point get_point(int id_0, int id_1)
{
    float s;
    s = (val - attributes[id_0])/(attributes[id_1] - attributes[id_0]);

    return Point(points[id_0].x + s*(points[id_1].x - points[id_0].x),
                 points[id_0].y + s*(points[id_1].y - points[id_0].y), 0);
}

std::pair<Point, Point> two_points(Cell cell)
{
    Point pts[2];
    int current=0;
    float _max, _min;
    _max = max(attributes[cell.ids[0]], attributes[cell.ids[1]]);
    _min = min(attributes[cell.ids[0]], attributes[cell.ids[1]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val)
    { pts[current++] = get_point(cell.ids[0], cell.ids[1]); }

    _max = max(attributes[cell.ids[1]], attributes[cell.ids[2]]);
    _min = min(attributes[cell.ids[1]], attributes[cell.ids[2]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val)
    { pts[current++] = get_point(cell.ids[1], cell.ids[2]); }

    _max = max(attributes[cell.ids[2]], attributes[cell.ids[3]]);
    _min = min(attributes[cell.ids[2]], attributes[cell.ids[3]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val)
    { pts[current++] = get_point(cell.ids[2], cell.ids[3]); }

    _max = max(attributes[cell.ids[0]], attributes[cell.ids[3]]);
    _min = min(attributes[cell.ids[0]], attributes[cell.ids[3]]);
    cout<<_max << " " << _min << endl;
    if (_max > val && _min < val)
    { pts[current++] = get_point(cell.ids[3], cell.ids[0]); }
    return std::make_pair(pts[0], pts[1]);
}

void drawContour()
{
    for(int i=0; i<25; ++i)
    {cout<<attributes[i]<<endl;}
    cout<<"******************"<<endl;
    for (auto cell : cells) {
        int intersections = n_intersections(cell);
        cout << intersections << endl;
        if (intersections == 2) {
            auto pts = two_points(cell);
            cout << pts.first.x << " " << pts.first.y << endl << pts.second.x << " " << pts.second.y << endl;
            glBegin(GL_LINES);
            //glColor3f(0, 0, 0);
            glVertex3f(pts.first.x, pts.first.y, 0);
            glVertex3f(pts.second.x, pts.second.y, 0);
            glEnd();
        }
    }
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

    //drawBox();
    drawContour();

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
    attributes.push_back(1);
    attributes.push_back(2);
    attributes.push_back(3);
    attributes.push_back(4);
    attributes.push_back(7);
    attributes.push_back(2);
    attributes.push_back(7);
    attributes.push_back(8);
    attributes.push_back(6);
    attributes.push_back(2);
    attributes.push_back(3);
    attributes.push_back(7);
    attributes.push_back(9);
    attributes.push_back(7);
    attributes.push_back(3);
    attributes.push_back(1);
    attributes.push_back(3);
    attributes.push_back(6);
    attributes.push_back(6);
    attributes.push_back(3);
    attributes.push_back(0);
    attributes.push_back(1);
    attributes.push_back(1);
    attributes.push_back(3);
    attributes.push_back(2);

    /*,2,3,4,7,
                 2,7,8,6,2,
                 3,7,9,7,3,
                 1,3,6,6,3,
                 0,1,1,3,2}; */
//    for(int i=0; i<25; ++i)
//    {points[i].z = attributes[i];}

    int szx=5;
    int szy=5;
    for(int j=0; j<4; ++j)
    {
        for(int i=0; i<4; ++i)
        {
            Cell c;
            c.ids[0] = j*szx+i;
            c.ids[1] = j*szx+i+1;
            c.ids[2] = (j+1)*szx+i+1;
            c.ids[3] = (j+1)*szx+i;
            cells.push_back(c);
        }
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
