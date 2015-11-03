#include <GL/glut.h> 
#include <iostream>
using namespace std;

bool keyStates[256]; 
int wWidth, wHeight;
bool isOrtho = true;
float cameraZLocation = 3;
float cameraAngle = 30;
float yRotation = 0;

void keyOperations (void) 
{
	if(keyStates[27] == true) {exit(0);}
	else if (keyStates['o'] == true) {isOrtho = true;}
	else if (keyStates['p'] == true) {isOrtho = false;}

	else if (keyStates['w'] == true) {cameraZLocation += 0.1;}
	//ovime se moze proci objekt, i cajnik je okrenut na drugu stranu
	else if (keyStates['s'] == true) {cameraZLocation -= 0.1;}

	else if (keyStates['x'] == true) {if(!isOrtho) {cameraAngle +=0.1;}}
	else if (keyStates['y'] == true) {if(!isOrtho) {cameraAngle -=0.1;}}

	else if (keyStates['r'] == true) {
		yRotation += 1.;
		if(yRotation>360) {yRotation -=360;}
	}
}

void reshape (int width, int height) 
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	wWidth = width;
	wHeight = height;
}

void keyPressed (unsigned char key, int /*x*/, int /*y*/) 
{
    keyStates[key] = true; 
    cout<<key<<" key pressed"<<endl;
}

void keyUp (unsigned char key, int /*x*/, int /*y*/) 
{
    keyStates[key] = false;
}
void drawObj()
{ glutWireTeapot(1); }

void drawHorzObj()
{
	double x0 = -5;
	double dx = 2.5;
	for(int i=0; i < 5; ++i)
	{
		glPushMatrix();
		glTranslatef(x0+i*dx, 0, 0-abs(2-i)*dx/4);
		drawObj();
		glPopMatrix();
	}
}
void drawVertObj()
{
	double x0 = -5;
	double dx = 2.5;
	for(int i=0; i < 5; ++i)
	{
		if(i!=2){
			glPushMatrix();
			glTranslatef(0, x0+i*dx, 0-abs(2-i)*dx/4);
			drawObj();
			glPopMatrix();
		}
	}
}

void display (void) 
{
    keyOperations();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if(isOrtho){
		//**** ortografska projekcija ****, u njoj gubimo osjecaj dubine
		//magnetska rezonancija, zanima nas koji je objekt u stvarnosti veci
		glOrtho(-5,5, -5, 5, 0.1, 100);
	}
	else {
		//**** perspektiva***
		//predstavlja nas stvarni svijet
		//slika se rasteze kako se rasteze prozor jer je to ploha na koju se sve projicira
		//gluPerspective(cameraAngle, 1, 0.1, 100);

		//fix
		gluPerspective(cameraAngle, (1. * wWidth)/wHeight, 0.1, 100);
	}
	
    
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();

	// x, y, z ; 1 je upvektor
	gluLookAt(0,0,cameraZLocation, 0,0,0, 0,1,0);
    //glutWireTeapot(1);

	// mjenjanje kamere, a ne objekte, rotacija
glPushMatrix();
	glRotatef(yRotation, 0, 1, 0);

    drawHorzObj();
    drawVertObj();
glPopMatrix();
    
    
    //glFlush(); // GLUT_SINGLE
    glutSwapBuffers(); // GLUT_DOUBLE 
}


int main (int argc, char **argv) 
{
    for(int i=0; i<256; ++i)
    { keyStates[i] = false; }
    glutInit(&argc, argv); 
    glutInitDisplayMode (GLUT_DOUBLE/*GLUT_SINGLE*/); 
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100); 
    glutCreateWindow ("v4"); 

    glutDisplayFunc(display); 

    glutIdleFunc(display); 

    glutReshapeFunc(reshape); 

    glutKeyboardFunc(keyPressed); 
    glutKeyboardUpFunc(keyUp); 

    glutMainLoop();
}
