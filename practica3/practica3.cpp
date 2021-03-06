//g++ file.cpp -o m -lGL -lGLU -lglut 
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

struct screenPt{
	GLint x;
	GLint y;
};
typedef enum { limacon = 1, cardioid, threeLeaf, fourLeaf, spiral } curveName;
GLsizei winWidth = 600, winHeight = 500; // Tamaño inicial de la ventana

void init (void){
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void lineSegment (screenPt pt1, screenPt pt2){//dibuja una linea
	glBegin (GL_LINES);
	glVertex2i (pt1.x, pt1.y);
	glVertex2i (pt2.x, pt2.y);
	glEnd ( );
}

void lineSegment(void){
  glClear(GL_COLOR_BUFFER_BIT); //borrar búferes a valores predeterminados
  glColor3f(0,0,1); // cambia el color de la linea (RGB)
  glLineWidth(6);
  glBegin(GL_LINES);
  glVertex2i(180,15);
  glVertex2i(10,145);
  glEnd();
  glFlush();
  //new line
  glColor3f(0,1,0);
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex2i(190,15);
  glVertex2i(20,145);
  glEnd();
  glFlush();
}

void drawCurve (GLint curveNum){
	const GLdouble twoPi = 6.283185;
	const GLint a = 175, b = 60;
	
	GLfloat r, theta, dtheta = 1.0 / float (a);	
	GLint x0 = 200, y0 = 250; // establecer posición inicial en la pantalla
	screenPt curvePt[2];
	glColor3f (0.0, 0.0, 0.0); // seleccionar negro como color de curva
	curvePt[0].x = x0; // inicializar posición de la curva
	curvePt[0].y = y0;
	switch (curveNum) { 
		case limacon:curvePt[0].x += a+b;break;
		case cardioid:curvePt[0].x += a+a;break;
		case threeLeaf:curvePt[0].x += a;break;
		case fourLeaf:curvePt[0].x += a;break;
		case spiral: break;
		default: break;
	}
	theta = dtheta;
	while (theta < twoPi) {
		switch (curveNum) {
			case limacon:
				r= a*cos(theta)+b; break;
			case cardioid:
				r= a*(1 + cos(theta)); break;
			case threeLeaf:
				r= a * cos(3 * theta); break;
			case fourLeaf:
				r= a * cos(2 * theta); break;
			case spiral:
				r=(a/4.0) * theta; break;
			default: break;
		}
		curvePt[1].x = x0 + r * cos (theta);
		curvePt[1].y = y0 + r * sin (theta);
		lineSegment (curvePt[0], curvePt[1]);
		curvePt[0].x = curvePt[1].x;
		curvePt[0].y = curvePt[1].y;
		theta += dtheta;
	}
}

void displayFcn (void){
	GLint curveNum;
	glClear (GL_COLOR_BUFFER_BIT); // Borrar ventana de visualización.
	cout << "\nEnter the integer value corresponding to\n";
	cout << "one of the following curve names.\n";
	cout << "Press any other key to exit.\n";
	cout << "\n1-limacon, 2-cardioid, 3-threeLeaf, 4-fourLeaf, 5-spiral: ";
	cin >> curveNum;
	if (curveNum == 1 || curveNum == 2 || curveNum == 3 || curveNum == 4 || curveNum == 5)
		drawCurve (curveNum);
	else
		exit (0);
	glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight){
	glMatrixMode (GL_PROJECTION); //especifica que matriz es la matriz actual
	glLoadIdentity();//reemplaza la matriz actual con la matriz de identidad
	gluOrtho2D (0.0, (GLdouble) newWidth, 0.0, (GLdouble) newHeight);
	glClear (GL_COLOR_BUFFER_BIT);
}

int main (int argc, char** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Dibujo de curvas");
	init ();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);//actualisa si hay cambios que mostrar 
	glutMainLoop ( );
}