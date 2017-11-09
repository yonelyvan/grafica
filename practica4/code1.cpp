//g++ file.cpp -o m -lGL -lGLU -lglut 
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

//dimensiones de ventana
int windowWidtb; 
int windowHeight;

void init (void){
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void test(void){
  glClear(GL_COLOR_BUFFER_BIT); //borrar búferes a valores predeterminados
  glColor3f(0,0,1); // cambia el color de la linea (RGB)
  glFlush();
}

void resize(GLsizei w, GLsizei h){
	//actualiza los valores glovales de tamaño de ventana
	windowWidtb =w;
	windowHeight =h;
	//pantalla completa
	glViewport(0,0,w,h);
	//inicia matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//configurar la pryeccion ortogonal
	glOrtho(0,w,0,h,1.f,-1.f);
	printf("resize: nuevo tamaño de ventana: %dx%d\n",w,h);
	//activa matriz del modelo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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