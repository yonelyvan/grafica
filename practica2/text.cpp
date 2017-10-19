
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

static char label[100];

void inline drawString (char *s)
{
 unsigned int i;
 for (i=0; i<strlen(s); i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
}

void init(void)
{
 glClearColor (0.0,0.0,0.0,1.0);
}

void reshape(int w, int h)
{
 if (!h)
	return;
 glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
 // Activamos la matriz de proyeccion.
 glMatrixMode(GL_PROJECTION);
 // "limpiamos" con la matriz identidad.
 glLoadIdentity();
 // usamos proyeccion ortogonal
 gluOrtho2D(0, w, 0, h);
 // se invierte el eje y, es decir, hacia abajo es positivo
 glScalef(1, -1, 1);
 // se mueve el origen de la esquina inferior izq.
 // hacia la esquina superior del mismo lado.
 glTranslatef(0, -h, 0);
 // activamos la matriz de modelado/visionado. 
 glMatrixMode(GL_MODELVIEW);
 // limpiamos la matriz
 glLoadIdentity();
}


void display(void)
{ 
 int i;
 double angulo;
 float x,y;
 char * nombre="angulo    sin(angulo)";

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode( GL_MODELVIEW_MATRIX );
 glLoadIdentity();

 glColor3f(0.1, 1.0, 0.1);
 sprintf(label,"%s", nombre);
 glRasterPos2f(95, 20);
 drawString (label);

 glColor3f(1.0, 1.0, 1.0);
 angulo=0.0;
 x=100;
 y=35;
 for (i=0; i<19; i++)
	{
	sprintf (label, "%4.1f      %4.5f",angulo, sin(angulo*PI/180));
	glRasterPos2f (x,y);
	drawString (label);
	angulo+=10;
	y=y+15;
	}
 glFlush();
} 

// Termina la ejecucion del programa cuando se presiona ESC
void keyboard(unsigned char key, int x, int y)
{
 switch (key) 
   {
   case 27: exit(0);
             break;
   }
}    

// Main del programa.
int main(int argc, char **argv)
{ 
 // Inicializo OpenGL
 glutInit(&argc, argv);
  // Activamos buffer simple y colores del tipo RGB  
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 // Definimos una ventana de medidas 300 x 300 como ventana 
 // de visualizacion en pixels
 glutInitWindowSize (300, 320);
  // Posicionamos la ventana en la esquina superior izquierda de 
 // la pantalla.
 glutInitWindowPosition (0, 0);
 // Creamos literalmente la ventana y le adjudicamos el nombre que se
 // observara en su barra de titulo.
 glutCreateWindow ("Texto en OpenGL");
 // Inicializamos el sistema 
 init();
 glutDisplayFunc(display); 
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutMainLoop();
  // ANSI C requiere que main retorne un valor entero.
 return 0;
}