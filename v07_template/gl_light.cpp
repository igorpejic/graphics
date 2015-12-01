#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>

GLfloat angle = 0.0;

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the  light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the  diffuse light to white
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse  light to white
GLfloat mShininess[] = {128}; //set the shininess of the material
GLfloat whiteAmbientLight[] = {1.0, 1.0, 1.0}; //set the  light ambient to white

bool diffuse = false;
bool emissive = false;
bool specular = false;
//normale
float nx=0.;
float ny=1.;
float nz=0.;

void init (void) {
    glEnable (GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void light (void) {
    //glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, whiteAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

float fun(const float& _x, const float& _z)
{
	//min -3, max 2
	//y = 0.1*(-x*x + -z*z) + 2; // analogija s y = -x^2, ali u 2. dimenzije
	return 0.1*(-_x*_x - _z*_z)+2;
}

float myColor(const float& v)
{
	float g = (v-(-3))/(2+3);
	return 1. -g;
}

// mreza kvadrata (sl. 20 iz 10-shading-opengl)
void drawMesh()
{
	/*
	std::vector<float> x(9);
	double x0 = -5;
	const double dx = 1.25;
	std::generate(x.begin(), x.end(), [&]{
		double v = x0;
		x0 += dx;
		return v;
	});
	*/
	uint num = 9;
	float x[num];
	for(uint i = 0; i < num; ++i)
	{ x[i] = -5 + i*1.25;}

	float z[num];
	for(uint i = 0; i < num; ++i)
	{ z[i] = -5 + i*1.25;}

	float myMaterial[4];
	myMaterial[2] = 1;
	myMaterial[3] = 1;

	glBegin(GL_QUADS);
	glNormal3f(nx, ny, nz);
	for(int i=0; i < num-1; ++i)
	{
		for(int j=0; j < num-1; ++j)
		{
			
			float v;
			v = fun(x[j], z[i]);
			glColor3f(myColor(v), myColor(v), 1);
			myMaterial[0] = myColor(v);
			myMaterial[1] = myColor(v);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myMaterial);
			glVertex3f(x[j], fun(x[j], z[i]), z[i]);

			v = fun(x[j+1], z[i]);
			glColor3f(myColor(v), myColor(v), 1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myMaterial);
			glVertex3f(x[j+1],fun(x[j+1], z[i]), z[i]);

			v = fun(x[j+1], z[i+1]);
			glColor3f(myColor(v), myColor(v), 1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myMaterial);
			glVertex3f(x[j+1],fun(x[j+1], z[i+1]), z[i+1] );

			v = fun(x[j], z[i+1]);
			glColor3f(myColor(v), myColor(v), 1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myMaterial);
			glVertex3f(x[j],fun(x[j], z[i+1]), z[i+1] );
		}
	}

		
	glEnd();

}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    light();
    glTranslatef(0,0,-15);
    
    glRotatef(90/*angle*/,1,1,1);
    
    //glutSolidTeapot(2);
    drawMesh();
    glutSwapBuffers();
    angle ++;
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
	if (key=='a')
	{
		nx -=0.05;
		if(nx<-1){nx=-1;}
	}
	else if(key=='d')
	{
		nx +=0.05;
		if(nx>1){nx=1;}
	}
	else if(key=='s')
	{
		nx +=0.05;
		if(ny>1){ny=1;}
	}
	else if(key=='w')
	{
		ny +=0.05;
		if(ny>1){ny=1;}
	}

	/*
    if (key=='s')
    {
        if (specular==false)
        {
            specular = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        }
        else if (specular==true)
        {
            specular = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blankMaterial);
        }
    }
    
    if (key=='d')
    {
        if (diffuse==false)
        {
            diffuse = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        }
        else if (diffuse==true)
        {
            diffuse = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
        }
    }
    
    if (key=='e')
    {
        if (emissive==false)
        {
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        }
        else if (emissive==true)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
        }
    }
	*/
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("GL Light");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutKeyboardFunc (keyboard);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
