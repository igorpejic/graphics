#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//n povrh k
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

// const obecaje se da se unutar koda nece mijenjati varijable poslane by referenece
// nije thread safe
double polyterm(const int& n, const int& k, const double& t)
{
	return pow( (1-t), n-k ) * pow(t, k);
}
double value(const double& t, const VectorXd& v){

    // 4 tocke, polinom reda 3
    int order = v.size()-1;
    double val=0;
    for(int i=0; i <= order; ++i){
	val+= binomials(order, i)*polyterm(order, i, t)*v(i);
    }
    return val;
	
}

double tangent(const double& t, const VectorXd& v){

    const int n = v.size()-1;
    VectorXd v2;
    v2.resize(n);
    for(int k=0; k < v2.size(); ++k){
    	v2(k) = n*(v(k+1) - v(k));
    }
    return value(t, v2);
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

    gluLookAt(0.0,0.0,15.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector

    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(pt_x(0), pt_y(0), 0.0f);
    glVertex3f(pt_x(1), pt_y(1), 0.0f);
    glVertex3f(pt_x(2), pt_y(2), 0.0f);
    glVertex3f(pt_x(3), pt_y(3), 0.0f);
    glEnd();

    // slajd 32, pred. 3
    /*
    {
    	Matrix4d m;
	    m << 1, 0,  0, 0,
        	-3, 3,  0, 0,
          	3, -6, 3, 0,
        	-1, 3, -3, 1;
	VectorXd ts = VectorXd::LinSpaced(11, 0, 1);
	VectorXd t_x, t_y;
	t_x.resize(ts.size()); t_y.resize(ts.size());
	//stupcasti vektor
	Vector4d t;
	for(int i=0; i < ts.size(); ++i){
	    t << 1, ts(i), pow(ts(i), 2), pow(ts(i), 3);
	    t_x(i) = t.transpose()*m*pt_x;
	    t_y(i) = t.transpose()*m*pt_y;
	}
	//GL_LINE_STRIP -crtanje polilinije
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<ts.size(); ++i)
	{
		glVertex3f(t_x(i), t_y(i), 0.);
	}
	glEnd();

    }
    */

    // slajd 21, pred. 3, treba dobiti w_i
   { 
    VectorXd ts = VectorXd::LinSpaced(11, 0, 1);
    VectorXd t_x, t_y;
    t_x.resize(ts.size()); t_y.resize(ts.size());
    //stupcasti vektor
    Vector4d t;
    for(int i=0; i < ts.size(); ++i){
    	t_x(i) = value(ts(i), pt_x);
    	t_y(i) = value(ts(i), pt_y);
    }
    glColor3f(1, 1, 0);
    glBegin(GL_LINE_STRIP);
    for(int i= 0; i < ts.size(); ++i)
    {
    	glVertex3f(t_x(i), t_y(i), 0.);
    }
    glEnd();
    }
    
    //slajd 34, pred. 3
    VectorXd ts = VectorXd::LinSpaced(11, 0, 1);
    VectorXd t_x, t_y; // tocke polinoma
    VectorXd tt_x, tt_y; // tocke tangenti
    t_x.resize(ts.size()); t_y.resize(ts.size());
    tt_x.resize(ts.size()); tt_y.resize(ts.size());
    for(int i=0; i < ts.size(); ++i){
    	t_x(i) = value(ts(i), pt_x);
    	t_y(i) = value(ts(i), pt_y);

	// dobije se tocka koja je negdje na pravcu tangente
    	tt_x(i) = tangent(ts(i), pt_x); 
    	tt_y(i) = tangent(ts(i), pt_y);
    }
    glColor3f(1, 0, 0);
    glBegin(GL_LINE);
    for(int i= 0; i < ts.size(); ++i)
    {
    	glVertex3f(tt_x(i), tt_y(i), 0.);
    }
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for(int i= 0; i < ts.size(); ++i)
    {
	glVertex3f(tt_x(i), tt_y(i), 0.);
    }
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
    /*
    for (int i = 0; i < pt_x.size(); ++i)
    {
    	pt2_x(i) = pt_x(i)+1.9;
    	pt3_x(i) = pt2_x(i)+1.9;
    }
    pt3_y = pt2_y = pt_y;
    */
	
    
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
