//g++ code2.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
#define PI 3.14159265

class scrPt{
    public:
       GLint x, y;
};

GLsizei winWidth = 200, winHeight = 150;

void init (void){
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}


void setPixel (GLint x, GLint y){
    glBegin (GL_POINTS);
    glVertex2i (x,y);
    glEnd();
}

void circlePlotPoints ( scrPt circCtr, scrPt circPt){
    setPixel (circCtr.x + circPt.x, circCtr.y + circPt.y);
    setPixel (circCtr.x - circPt.x, circCtr.y + circPt.y);
    setPixel (circCtr.x + circPt.x, circCtr.y - circPt.y);
    setPixel (circCtr.x - circPt.x, circCtr.y - circPt.y);
    setPixel (circCtr.x + circPt.y, circCtr.y + circPt.x);
    setPixel (circCtr.x - circPt.y, circCtr.y + circPt.x);
    setPixel (circCtr.x + circPt.y, circCtr.y - circPt.x);
    setPixel (circCtr.x - circPt.y, circCtr.y - circPt.x);
}

void circleMidpoint (scrPt circCtr, GLint radius){
    scrPt circPt;
    GLint p = 1 - radius;  
    circPt.x=0;
    circPt.y=radius;
    circlePlotPoints(circCtr,circPt);
    //cout<<"dlñuasld"<<endl;
    while (circPt.x < circPt.y) {
        circPt.x++;
        if (p < 0)
            p += 2 * circPt.x + 1;
        else {
            circPt.y--;
            p += 2 * (circPt.x - circPt.y) + 1;
        }
        circlePlotPoints(circCtr, circPt);
    }
}


void pieChart (void){
    scrPt circCtr, piePt;
    GLint radius = winWidth / 4;               

    GLdouble sliceAngle, previousSliceAngle = 0.0;

    GLint k, nSlices = 12;//numero de particiones 
    GLfloat dataValues[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
                               3.0, 16.0, 5.0, 3.0, 17.0, 8.0};
    GLfloat dataSum = 0.0;

    circCtr.x = winWidth/2;                 
    circCtr.y = winHeight/2;

    circleMidpoint (circCtr, radius);  

    //codigo para dibujar las particiones
    for (int i = 0; i < nSlices; ++i)//sumar valores de dataValues
        dataSum += dataValues[i];

    for (int i = 0; i < nSlices; i++) {
        sliceAngle = 2*PI * dataValues[i] / dataSum + previousSliceAngle;
        piePt.x = circCtr.x + radius * cos(sliceAngle);
        piePt.y = circCtr.y + radius * sin(sliceAngle);
        glBegin (GL_LINES);
            glVertex2i (circCtr.x, circCtr.y);
            glVertex2i (piePt.x, piePt.y);
        glEnd ( );
        previousSliceAngle = sliceAngle;
    }
}

void displayFcn (void){
    glClear (GL_COLOR_BUFFER_BIT);   
    glColor3f (0.0, 0.0, 1.0);       
    pieChart ();
    glFlush ();
}


int main (int argc, char** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Pie Chart");

    init ( );
    glutDisplayFunc (displayFcn);
    glutMainLoop ( );
    return 0;
}