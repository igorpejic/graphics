#include <stdlib.h>
#include <GL/glut.h>

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

	// renderira sve sto je manje od 1 i od 1000 od mene, zato se na pocetku nije nista vidjelo
    gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
    /*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, // camera
		      0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector
    */


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
void drawTriangle(){
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
}
void drawPentagon(){
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
}

void drawTrapezoid(){
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);	
}
void drawNT(int n){
	for (int i = 0; i < n; i++){
        glPushMatrix();
		glRotatef((360/n)*i, 0, 0, 1);
		glTranslatef(1, 0, 0);
		glBegin(GL_QUADS);
		drawTrapezoid();
		glEnd();
		glPopMatrix();
	}

}

void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
	glLoadIdentity(); // resetiranje

	//posljednji red: kako kamera stoji	  
	gluLookAt(0, 0, 5,
	          0, 0, -1,
		  0, 1, 0);

	//translatiraj objekt po z-u za -5, primjenjuje se na cijelu scenu; svi objekti
	//gl-smurf naming
	//f-floating point, glTranslatei- integer
	glTranslatef(0, 0, -5);

    //rotiraj citavu scenu
    glRotatef(_angle, 0, 0, 1);

	// ogranici transformaciju samo na ovaj objekt
	glPushMatrix();
	drawNT(4);
	glPopMatrix();
	// kraj ogranicenja
		
	glPushMatrix();
	glTranslatef(0, -1, 0);
	glBegin(GL_TRIANGLES);
	//Pentagon
	//drawPentagon();
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 0, 0);
	glBegin(GL_TRIANGLES);
	//Triangle
	//drawTriangle();
	glEnd();
	glPopMatrix();
	glRotatef(_angle, 0, 0, 1);
		
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("v4 - p1");
	// reakcija na promjenu prozora
	glutReshapeFunc(changeSize);

	glutDisplayFunc(drawScene);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
