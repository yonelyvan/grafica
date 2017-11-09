//g++ file.cpp -o m -lGL -lGLU -lglut 
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//dimensiones de ventana
int windowWidtb; 
int windowHeight;

//variables control de punto
int xi, xf, xt;
int yi, yf, yt;

//configuracion inical del programa
void init (void){
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
}
//funcion principal de despliege
void display(void){
	int i;
	//limpiar pantalla
	glClearColor(GL_COLOR_BUFFER_BIT);
	//pinta rectangulo gris con el  arrastre
	glColor3ub(192,192,192);
	glBegin(GL_POINTS);
	for (i =xi ; i <xf ; ++i)
		glVertex2i(i,yi), glVertex2i(i,yf);
	for (i =yi ; i <yf ; ++i)
		glVertex2i(xi,i), glVertex2i(xf,i);
	for (i =xi ; i <xf ; ++i)
		glVertex2i(i,yi), glVertex2i(i,yf);
	for (i =yi ; i <yf ; ++i)
		glVertex2i(xi,i), glVertex2i(xf,i);
	glEnd();

	//activa el pintado de pixeles

}

int main (int argc, char** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (200, 200);
	glutCreateWindow ("Dibujo de curvas");
	init();
	glutDisplayFunc(test);
	glutReshapeFunc(resize);//actualisa si hay cambios que mostrar 
	glutMainLoop ( );
}