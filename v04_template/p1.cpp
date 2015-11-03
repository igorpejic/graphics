#include <GL/glut.h> 
#include <iostream>
using namespace std;

bool keyStates[256]; 

void keyOperations (void) 
{
}

void reshape (int width, int height) 
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void keyPressed (unsigned char key, int x, int y) 
{
    keyStates[key] = true; 
    cout<<key<<" key pressed"<<endl;
}

void keyUp (unsigned char key, int x, int y) 
{
    keyStates[key] = false;
}

void display (void) 
{
    keyOperations();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    
    
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();
    
    
    
    
    
    
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
