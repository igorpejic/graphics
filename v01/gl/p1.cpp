#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
class Point
{
public:
    Point(const double& _x, const double& _y) : m_x(_x), m_y(_y), m_z(0.){}
    //konstruktor, sve u istom redu,
    //odmah se stavlja vrijednost u objekt prilikom instanciranja
    Point(const Point& other) {m_x = other.m_x; m_y = other.m_y; m_z = other.m_z; }
    Point& operator = (const Point& other) {m_x = other.m_x; m_y = other.m_y; m_z = other.m_z;  return *this;}
    double x() const {return m_x;}
    double y() const {return m_y;}
    double z() const {return m_z;}
private:
    double m_x,m_y,m_z;
};

class Grid
{
public:
    Grid(const int& numr, const int& numd, const double &phi) : m_r(numr), m_degs(numd), m_phi(phi * 3.14159 / 180.0)
    { generatePoints();}
    std::vector<Point> quad(size_t idx)
    {
        // TODO
        // return pts in quad
        std::vector<Point> pts;
        pts.push_back(m_pts[idx]);
        pts.push_back(m_pts[idx+m_degs+1]);
        pts.push_back(m_pts[idx+m_degs+1+1]);
        pts.push_back(m_pts[idx+1]);

        //return by value-kompajler optimira
        return pts;
    }
    int degs() const {return m_degs;}
    int rads() const {return m_r;}
private:
    void generatePoints()
    {
        //double x, y;
        //m_pts.push_back(Point(x, y));

        double r0=0.5;
        double r1=0.9;
        double dr=(r1-r0)/m_r;
        double d0=0.; double d1= m_phi;
        double dd=(d1-d0)/m_degs;

        for(int ri=0; ri<=m_r; ++ri){
            for(int di=0; di<=m_degs; ++di){
                double r = r0+ri*dr;
                double deg = d0+di*dd;
                double x = r*cos(deg);
                double y = r*sin(deg);
                m_pts.push_back(Point(x,y));
            }
        }

        //const- vrijednost na toj adresi se ne moze mijenjati
        //for(const Point& pt : m_pts){ ISTO JE
        for(const auto& pt : m_pts){
                std::cout<<pt.x()<<", "<<pt.y()<<std::endl;
        }
        // TODO
        // r = 0.5 : 0.95
        // x = r \times cos(\alpha)
        // y = r \times sin(\alpha)
        // -1 < x,y < 1

    }

    //m-member varijabla
    const int m_r;
    const int m_degs;
    const double m_phi;
    std::vector<Point> m_pts;
};

Grid g(5, 6, 90.);
//10 podjela po r, 10 po fi, zakrenuto za 90 stupnjeva
//Grid g(10,10,90.);
void changeSize(int w, int h) 
{
	if(h == 0) { h = 1;}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, // camera
		      0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector
}

void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
	glLoadIdentity(); // resetiranje
	
	glBegin(GL_QUADS);

        //std::vector<Point> pts = g.quad(??);
        for(int ri=0; ri<g.rads(); ri++)
        {
                for(int di=0; di<g.degs(); di++)
                {
                        int idx = di+ri*(g.degs()+1);
                        auto pts = g.quad(idx);
                        for(auto pt: pts)
                        {
                                glVertex3f(pt.x(), pt.y(), pt.z());
                        }
                }
        }

    // TODO
    // nacrtati Grid kvadrate
    // TOCKE KVADRATA: i, i+1, i+broj_podjela po kutu, i+broj_podjela po kutu -1
    glVertex3f(-0.9f, -0.9f, 0.0f);
    glVertex3f(-0.5f, -0.9f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glVertex3f(-0.9f, 0.5f, 0.0f);

    glVertex3f(-0.4f, -0.9f, 0.0f);
    glVertex3f(-0.f, -0.9f, 0.0f);
    glVertex3f(-0.f, 0.3f, 0.0f);
    glVertex3f(-0.4f, 0.3f, 0.0f);

	glEnd();
		
	glutSwapBuffers();
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

    glutCreateWindow("v1 - p1");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(drawScene);
    glutMainLoop();
	return 0;
}
