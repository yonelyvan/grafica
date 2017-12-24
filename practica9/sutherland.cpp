// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define TAM_VENTANA_X 600 
#define TAM_VENTANA_Y 600
using namespace std;
#define show(x) cout<<#x<<" "<<x<<endl;

float angulo =0.0; //angulo inicial
float posicion[2]={TAM_VENTANA_X/2.0,TAM_VENTANA_Y/2.0}; //pos inicial

 
 /************************************************************************/
/* ALGORITMO DE RECORTE DE COHEN SUTHERLAND *****************************/
/* SI DEVUELVE TRUE, ES RECORTADO ***************************************/
/* SI DEVUELVE FALSE, NO LO ES ******************************************/
/* EN LOS PARAMETROS POR REFERENCIA *************************************/
/* SE ENCUENTRAN LOS NUEVOS PUNTOS DEL SEGMENTO *************************/
/************************************************************************/

//extremos de la ventana de recorte
float xmin,ymin,xmax,ymax;
void configuraventana(){
	xmin = TAM_VENTANA_X / 3.0;
	ymin = TAM_VENTANA_Y / 3.0;
	xmax = 2*TAM_VENTANA_X / 3.0;
	ymax = 2*TAM_VENTANA_Y / 3.0;
	show(xmin);
	show(xmax);
	show(ymin);
	show(ymax);
}

void init(){
	glClearColor(1,1,1,1.0);
	glClear(GL_COLOR_BUFFER_BIT); 
	gluOrtho2D(xmin,xmax,ymin,ymax);
	glFlush();
}


int Cohen_Suth(float x0,float y0,float x1,float y1,float *xdef0,float *ydef0,float *xdef1,float *ydef1);

void lineTo(float x, float y){
	float xdef0,ydef0, xdef1, ydef1;
	int resul;
	resul =
	Cohen_Suth(posicion[0],posicion[1],x,y,&xdef0,&ydef0,&xdef1,&ydef1);
	if(resul == TRUE){
		glBegin(GL_LINES);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(posicion[0],posicion[1]);
		glVertex2f(xdef0,ydef0);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(xdef0,ydef0);
		glVertex2f(xdef1,ydef1);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(xdef1,ydef1);
		glVertex2f(x,y);
		glEnd();
	}
	else{
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2f(posicion[0],posicion[1]);
		glVertex2f(x,y);
		glEnd();
	}
	glFlush();
	posicion[0] = x;
	posicion[1] = y;
}






int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("OpenGL");

	configuraventana();
	init();
	glutDisplayFunc(lineTo); 
	glutMainLoop(); 
	exit(0);
}



