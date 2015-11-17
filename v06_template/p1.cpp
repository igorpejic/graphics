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

void drawBezierCurve()
{
    glPushMatrix();
    glColor3f ( 1.0f, 0.0f, 0.0f );
    glBegin ( GL_LINE_STRIP );
    for ( int i=0; i< ts.size(); ++i )
    { glVertex3f ( t_x ( i ), t_y ( i ), t_z ( i ) ); }
    glEnd();
    glPopMatrix();

}

Vector3d sphere_coo;
Vector3d cube_coo;
float dist;

void drawSphere()
{
    float x,y,z;
    x = getValue(dist, pt_x);
    y = getValue(dist, pt_y);
    z = getValue(dist, pt_z);
    glPushMatrix();
    glTranslatef(x,y,z);
    glutWireSphere(0.2, 16,16);
    glPopMatrix();
    
}
float cone_angle = -90;
void drawCone()
{
    glPushMatrix();
    glColor3f ( 0.0f, 1.0f, 0.0f );
    glutWireCone(0.2, 0.8, 16,4);
    glPopMatrix();
}

void solidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    glBegin(GL_LINE_LOOP);
    
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    
    gluSphere(quadric, radius, slices, stacks);
    
    gluDeleteQuadric(quadric);
    glEnd();
}

void drawTriquad()
{
    glPushMatrix();
    glTranslatef(2,0,0);
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd();
    glPopMatrix();
    
    glBegin(GL_QUADS);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0.8, 0.8 );
    glColor3f( 1, 1, 0 ); // blue
    glVertex2f( -0.8, 0.8 );
    glEnd();
}
void drawTriFan2d()
{
    float coords[] = { -0.5, -0.5,  0.5, -0.5,  0.5, 0.5,  -0.5, 0.5 };

    glColor3f( 1, 0.3, 0.3 ); // red
    glBegin(GL_TRIANGLE_FAN);
    glVertex2fv(coords);
    glVertex2fv(coords + 2);
    glVertex2fv(coords + 4);
    glVertex2fv(coords + 6);
    glEnd();
}
void drawScene()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor (0.3, 0.3, 0.3, 0.0);
    
    glMatrixMode ( GL_MODELVIEW ); // idemo u perspektivu
    glLoadIdentity(); // resetiranje

    gluLookAt ( 0.0,0.0,10.0, // camera
                0.0,0.0,-1.0, // where
                0.0f,1.0f,0.0f ); // up vector
    drawTriquad();

    /*drawTriFan2d();*/

    glPushMatrix();
        glRotatef(cone_angle, 0,1,0);
        drawCone();
        // crtanje bezierove krivulje
        glPushMatrix();
            glRotatef(-90, 0,1,0);

            glTranslatef(0.95,0.5,0);
            glPushMatrix();
                drawSphere();
            glPopMatrix();
            drawControlPoints();
            drawBezierCurve();
        glPopMatrix();
    glPopMatrix();
    
    glutSwapBuffers();
}


void update ( int /*value*/ )
{
    glutPostRedisplay();
    cone_angle += 1;
    dist = 1 - cone_angle/(0-90);
    if(cone_angle > 0 ){cone_angle = -90;}
    //update glut-a nakon 25 ms
    glutTimerFunc ( 25, update, 0 );
}


int main ( int argc, char **argv )
{
    pt_x << -0.95, -0.25, 0.6, 0.95;
    pt_y << -0.5, 0.8, 0.6, -0.5;
    pt_z << 0, 0, 0, 0;
    dist = 0.;
    generateBezierCurve();

    sphere_coo << pt_x(0), pt_y(0), pt_z(0);
    cube_coo << 0, 0, 0;
    glutInit ( &argc, argv );
    
    glutInitDisplayMode ( GLUT_DOUBLE /*| GLUT_RGB | GLUT_DEPTH */);
    glutInitWindowSize ( 400, 400 );
    
    glutCreateWindow ( "v6 - p1" );
    glutReshapeFunc ( changeSize );
    glutDisplayFunc ( drawScene );
    glutTimerFunc ( 25, update, 0 );
    glShadeModel (/*GL_SMOOTH*/GL_FLAT);
    glutMainLoop();

    return 0;
}