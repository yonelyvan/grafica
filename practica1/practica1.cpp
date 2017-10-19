//g++ practica1.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <iostream>
using namespace std;
void init(){
  glClearColor(0.3,0.3,0.3,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,200.0,0.0,200.0);//establece una región de visualización
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

//5
void home5(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,0,1); 
  glLineWidth(6);
  glBegin(GL_LINES);
  int x=50, y=50,t=4;
  //paredes
  glVertex2i(x+0*t,y+0*t);
  glVertex2i(x+10*t,y+0*t);
  glVertex2i(x+0*t,y+0*t);
  glVertex2i(x+0*t,y+10*t);
  glVertex2i(x+10*t,y+0*t);
  glVertex2i(x+10*t,y+10*t);
  glEnd();
  glFlush();
  //techo
  glColor3f(0,1,0); 
  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex2i(x-5*t,y+10*t);
  glVertex2i(x+15*t,y+10*t);
  glVertex2i(x+5*t,y+15*t);
  glVertex2i(x+15*t,y+10*t);
  glVertex2i(x+5*t,y+15*t);
  glVertex2i(x-5*t,y+10*t);
  glEnd();
  glFlush();
}


class class_home{
public:
	int pos_x;
	int pos_y; 
	int dim;//dimension proporcion de paredes y techo
	int t;//factor para redimensionar
	class_home(int pos_x_, int pos_y_, int d_, int t_){
		pos_x=pos_x_;
		pos_y=pos_y_;
		dim=d_;
		t=t_;
	}
};
//6
void home(void){
	class_home h(100,50,2,10); //clase home
	int x=h.pos_x, y=h.pos_y;//posicion
  	int n=h.dim;
  	int t=h.t;

  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(0,0,1); 
  	glLineWidth(6);
  	glBegin(GL_LINES);
  	//paredes
  	glVertex2i(x,y);
  	glVertex2i(x+n*t,y);
  	glVertex2i(x,y);
  	glVertex2i(x,y+n*t);
  	glVertex2i(x+n*t,y);
  	glVertex2i(x+n*t,y+n*t);
  	glEnd();
  	glFlush();
  	//techo
  	glColor3f(0,1,0); 
  	glLineWidth(3);
  	glBegin(GL_LINES);
  	glVertex2i(x-n*t,y+n*t);
  	glVertex2i(x+2*n*t,y+n*t);//base
  	glVertex2i(x+(n/2)*t,y+2*n*t);
  	glVertex2i(x+2*n*t,y+n*t); //r
  	glVertex2i(x+(n/2)*t,y+2*n*t);
  	glVertex2i(x-n*t,y+n*t);//l
  	glEnd();
  	glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(400,300);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    glutDisplayFunc(home); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
