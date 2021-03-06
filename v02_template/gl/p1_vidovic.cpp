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
    glBegin(GL_TRIANGLES);
    //Triangle
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();
}
void drawPentagon(){
    glBegin(GL_TRIANGLES);
    //Pentagon
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);

    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);

    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
}
void drawTrapezoid(){
    glBegin(GL_QUADS);
    //Trapezoid
    glVertex3f(-0.7f, -0.5f, 0.0f);
    glVertex3f(0.7f, -0.5f, 0.0f);
    glVertex3f(0.4f, 0.5f, 0.0f);
    glVertex3f(-0.4f, 0.5f, 0.0f);
    glEnd();
}
void drawNT(int n){
    drawAxis(1);
    for(int i=0; i<n;i++){
        glPushMatrix();
        glRotatef(i*360/n,0,0,1);
        glTranslatef(1,0,0);
        drawTrapezoid();
        glPopMatrix();
    }
}

void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); // idemo u perspektivu
	glLoadIdentity(); // resetiranje
	
    gluLookAt(0,0,5,    //pozicija kamere
              0,0,-1,   //gdje gledas
              0,1,0);  //nagib kamere
    glTranslatef(0,0,-5);  //mice scenu


 /*
    glPushMatrix();
    glRotatef(_angle,0,0,1);
    //glTranslatef(0,1,0);
    drawAxis(0.9);
    //glRotatef(_angle,0,1,0);
    glTranslatef(1,1,0);
    drawAxis(0.7);
*/
    /*glBegin(GL_QUADS);
	//Trapezoid
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);	
    glEnd();	*/
 /*   drawTrapezoid();
    glPopMatrix();
 */
    glPushMatrix();
    glRotatef(_angle,0,0,1);
    drawNT(4);
    glPopMatrix();









    // ----------------------------------


  //  glPushMatrix();
  //  glTranslatef(0,-1,0);
    /*glBegin(GL_TRIANGLES);
	//Pentagon
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();*/
  //  drawPentagon();
  //  glPopMatrix();
	
/*    glPushMatrix();
    glTranslatef(1,0,0);
    glRotatef(_angle*1.5,1,0,0);
*/
    /*glBegin(GL_TRIANGLES);
	//Triangle
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();*/
//    drawTriangle();
//    glPopMatrix();




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
	glutReshapeFunc(changeSize);
	glutDisplayFunc(drawScene);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
