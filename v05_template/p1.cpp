#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;


long binomials ( long n, long k )
{
    // n && k >=0
    long i;
    long b;

    if ( 0 == k || n == k )
    {
        return 1;
    }

    if ( k > n )
    {
        return 0;
    }

    if ( k > ( n - k ) )
    {
        k = n - k;
    }

    if ( 1 == k )
    {
        return n;
    }

    b = 1;

    for ( i = 1; i <= k; ++i )
    {
        b *= ( n - ( k - i ) );

        if ( b < 0 ) return -1; /* ERR!!!! OVERFLOW */

        b /= i;
    }

    return b;
}

double polyterm ( const int &n, const int &k, const double &t )
{
    return pow ( ( 1.-t ),n-k ) *pow ( t,k );
}

double getValue ( const double &t, const VectorXd &v )
{
    int order = v.size()-1;
    double value = 0;

    for ( int n=order, k=0; k<=n; k++ )
    {
        if ( v ( k ) ==0 ) continue;

        value += binomials ( n,k ) * polyterm ( n,k,t ) * v ( k );
    }

    return value;
}

void changeSize ( int w, int h )
{
    if ( h == 0 )
    {
        h = 1;
    }

    float ratio = 1.0* w / h;

    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    glViewport ( 0, 0, w, h );
    gluPerspective ( 45,ratio,1,1000 ); // view angle u y, aspect, near, far
}

Vector4d pt_x, pt_y, pt_z;
VectorXd t_x, t_y, t_z;
VectorXd ts;


void drawControlPoints()
{
    glPushMatrix();
    glColor3f ( 1.0f, 1.0f, 1.0f );
    glBegin ( GL_LINE_STRIP );
    glVertex3f ( pt_x ( 0 ), pt_y ( 0 ), pt_z ( 0 ) );
    glVertex3f ( pt_x ( 1 ), pt_y ( 1 ), pt_z ( 1 ) );
    glVertex3f ( pt_x ( 2 ), pt_y ( 2 ), pt_z ( 2 ) );
    glVertex3f ( pt_x ( 3 ), pt_y ( 3 ), pt_z ( 3 ) );
    glEnd();
    glPopMatrix();
}

void generateBezierCurve()
{
	ts = VectorXd::LinSpaced ( 21,0,1. );
	t_x.resize ( ts.size() );
	t_y.resize ( ts.size() );
	t_z.resize ( ts.size() );

	for ( int idx=0; idx< ts.size(); ++idx )
	{
		t_x ( idx ) = getValue ( ts ( idx ), pt_x );
		t_y ( idx ) = getValue ( ts ( idx ), pt_y );
		t_z ( idx ) = getValue ( ts ( idx ), pt_z );
        }
}

// draw i kreira tocke i crta, trebalo bi raditi jednu stvar
void drawBezierCurve()
{
    glPushMatrix();
    glColor3f ( 1.0f, 0.0f, 0.0f );
    glBegin ( GL_LINE_STRIP );
    for ( int i=0; i< ts.size(); ++i )
    {
        glVertex3f ( t_x ( i ), t_y ( i ), t_z ( i ) );
    }
    glEnd();
    glPopMatrix();
}

Vector3d sphere_coo;
Vector3d cube_coo;
void drawSphere()
{
    glPushMatrix();
    glTranslatef(sphere_coo(0), sphere_coo(1), sphere_coo(2));
    glutWireSphere(0.2, 16,16);
    glPopMatrix();
    
}
float angle_0=-90;
float angle_n=0;

float angle = -90;
void drawCone()
{
    glPushMatrix();
	angle += 1;
	if (angle > 0) { angle = 0; }
    glColor3f ( 0.0f, 1.0f, 0.0f );
    glTranslatef(cube_coo(0), cube_coo(1), cube_coo(2));
	glRotatef(angle, 0, 1, 0);
    glutWireCone(0.2, 0.8, 16,4);
    glPopMatrix();
}

/*
//graf scene
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;
class SceneNode
{
public:
    void addChild(shared_ptr<SceneNode> node){ m_children.push_back(node);}
    
    void update() const 
    {
        glPushMatrix();
        // postavimo si nekakvu matricu transformacije
        // i prebacimo u c array
	// push i pop koristiti je sporiji nacin
        float* arr;
        Map<Matrix4f>( arr, m_tM.rows(), m_tM.cols() ) =   m_tM;
        glLoadMatrixf(arr);
        for(const auto& child: m_children)
        {child->update();}   
        glPopMatrix();
    }

protected:
    // kako crtati, ili ipak ne
    // virtual void drawSelf() const {*ovdje se odvija crtanje*};
private:
	// lista pointera na sceneNode
    vector<shared_ptr<SceneNode>> m_children;
    // tranformacija
    Matrix4f m_tM;
};
*/

void drawScene()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode ( GL_MODELVIEW ); // idemo u perspektivu
    glLoadIdentity(); // resetiranje

    gluLookAt ( 0.0,0.0,10.0, // camera
                0.0,0.0,-1.0, // where
                0.0f,1.0f,0.0f ); // up vector
	/*
    drawControlPoints();

    drawBezierCurve();
    
    drawSphere();
	*/
	glPushMatrix();
		glRotatef(angle, 0, 1, 0);
	        drawCone();
		glPushMatrix();
			//translatirati kontrolne tocke u 0, 0
			//glTranslatef(0.95, 0.5, 0);
			glTranslatef(-pt_x(0), -pt_y(0), -pt_z(0));
			drawControlPoints();
		   drawBezierCurve();
		   drawSphere();
		glPopMatrix();
	glPopMatrix();
    
    glutSwapBuffers();
}


void update ( int /*value*/ )
{
    glutPostRedisplay();
	// opcenita formula
	// x = (alfa - alfa_0)/(alfa_n - alfa_0) -- alfa_n maksimalni
	if(angle <0)
	{
		double t = (angle - angle_0)/(angle_n - angle_0);
		sphere_coo(0) = getValue(t, pt_x);
		sphere_coo(1) = getValue(t, pt_y);
		sphere_coo(2) = getValue(t, pt_z);
	} else {
		// za animaciju povratak ovdje staviti counter
		// ne radi  = 0 jer je translatiran koo sustav
		sphere_coo(0) = pt_x(0);
		sphere_coo(1) = pt_y(0);
		sphere_coo(2) = pt_z(0);
	}
	//angle += (angle_n - angle_0)/fabs(angle_n-angle_0);
	angle += 1;
	if (angle > 0){angle=0;}
    //update glut-a nakon 25 ms
    glutTimerFunc ( 25, update, 0 );
}


int main ( int argc, char **argv )
{
    
    pt_x << -0.95, -0.25, 0.6, 0.95;
    pt_y << -0.5, 0.8, 0.6, -0.5;
    pt_z << 0, 2, 4, 6;
	angle = angle_0;
	generateBezierCurve();
    
    sphere_coo << pt_x(0), pt_y(0), pt_z(0);
    cube_coo << 0, 0, 0;
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize ( 400, 400 );

    glutCreateWindow ( "v3 - p1" );
    glutReshapeFunc ( changeSize );
    glutDisplayFunc ( drawScene );
    glutTimerFunc ( 25, update, 0 );
    glutMainLoop();

    return 0;
}
