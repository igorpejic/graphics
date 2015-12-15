#include <GL/gl.h>

#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>


void drawNormal(float p0[3], float p1[3] )
{
    const float size=1.;
    // draw axis
    glLineWidth(8);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(p0[0],p0[1],p0[2]);
        glVertex3f(p1[0],p1[1],p1[2]);
    glEnd();
    glLineWidth(1);

    glColor3f(1, 1, 1); // restore color
}

void drawScene()
{
    glClearColor(0.9f, 0.92f, 0.94f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_FLAT/*GL_SMOOTH*/);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    float p0[3]={0,0,0};
    float p1[3]={1,1,1};
    drawNormal(p0,p1);
    glutSwapBuffers();
    glutPostRedisplay();
}



void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    }
}
void handleResize(int w, int h)
{
    /*glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);*/

    if (h == 0) { h = 1; }
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45,ratio,1,1000); // view angle u y, aspect, near, far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, // camera
              0.0,0.0,-1.0, // where
              0.0f,1.0f,0.0f); // up vector
}

void initRendering()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT,GL_DIFFUSE);

    float black[4]={0,0,0,0};

    glMaterialfv(GL_FRONT,GL_AMBIENT,black);
    glMaterialfv(GL_FRONT,GL_SPECULAR,black);
    glEnable(GL_CULL_FACE);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    //Create the window
    glutCreateWindow("normale...");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutMainLoop();
    return 0;
}

