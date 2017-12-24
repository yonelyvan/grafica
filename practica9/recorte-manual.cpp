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

 


void turnTo(float angle){
	angulo = angle;
}

void turn(float angle){
	angulo+=angle;
}

void moveTo(float x, float y){
	posicion[0] = x;
	posicion[1] = y;
}
void lineTo(float x, float y){
	glColor3f(0,0,0);
	//ATENCION. PONER AQUI LA LLAMADA A COHEN _ SUHTHERLAND
	//LAS DOS DECLARCIONES SIGUIENTES SON PARA CUANDO SE USE C-H
	int resul;
	float xdef0,ydef0, xdef1, ydef1;
	glBegin(GL_LINES);
	glVertex2f(posicion[0],posicion[1]);
	glVertex2f(x,y);
	glEnd();
	posicion[0] = x;
	posicion[1] = y;
	glFlush();
}

void forward(float dist, int isvisible){
	const float Radsperdegree = 0.017453393;
	float x = posicion[0]+ dist * cos(Radsperdegree*angulo);
	float y = posicion[1]+ dist * sin(Radsperdegree*angulo);
	if(isvisible)
		lineTo(x,y);
	else
		moveTo(x,y);
	glFlush();
}


float L=15.5;
void motivo(){
	for (int i = 0; i < 4; ++i){
		forward(3*L,1);
		turn(90);
		forward(L,1);
		turn(90);
		forward(L,1);
		turn(90);
	}

}


float length=100.0;
float incremento=2.0;
float angulo_ = 170;
void polyespiral(){
	int i;
	for(i=0;i<50;i++){
		forward(length,1);
		turn(angulo_);
		length+= incremento;
	}
}





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
	//xmin = 0.0;
	//ymin = 0.0;
	//xmax = 600.0;
	//ymax = 600.0;
}

void init(){
	glClearColor(1,1,1,1.0);
	glClear(GL_COLOR_BUFFER_BIT); //establece el modo de matriz actual.
	gluOrtho2D(xmin,xmax,ymin,ymax);//establece una región de visualización
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("OpenGL");

	configuraventana();
	init();
	//glutDisplayFunc(motivo); 
	glutDisplayFunc(polyespiral); 
	glutMainLoop(); 
	exit(0);
}
