//g++ line.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
#define see(x) cout<<#x<<" "<<x<<endl;
#define see_point(x,y) cout<<#x<<" "<<#y<<" : "<<x<<" "<<y<<endl;

#define PI 3.14159265
#define x first
#define y second
typedef pair<int,int> point;


int x_init=5, y_init=5;
int px=4;
int dim=97;


void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,400.0,0.0,400.0);//establece una región de visualización
}


void plano(){
  //tablero
  glBegin(GL_LINES);
  glColor3f(0.85,0.85,0.85);
  //plano de 30x30
  for (int i = 0; i <= dim; ++i){
    //horizontales
    glVertex2i(x_init+ 0,y_init+ px*i);
    glVertex2i(x_init+ dim*px,y_init+ px*i);
    //verticales
    glVertex2i(x_init+ px*i,y_init+ 0);
    glVertex2i(x_init+ px*i,y_init+ dim*px);
  }
  glEnd();
  glFlush();
}


void set_pixel(int xi, int yi){
  glBegin(GL_POINTS);
  glColor3f(0,0,0);
  int x =x_init+ xi*px;
  int y =y_init+ yi*px;
  for (int i = 0; i < px; ++i){
    for (int j = 0; j < px; ++j){
      glVertex2i(x+i, y+j);
    }
  }
  glEnd();
  glFlush();
}


/*dibujando lineas*/
void ln(point p1, point p2){//simple espejando en funcion de x 
	if(p1.x>p2.x){
		point temp=p1;
		p1=p2;
		p2=temp;
	}
  	float dy = p2.y-p1.y;
  	float dx = p2.x-p1.x;
	float m=dy/dx;//pendiente 
  	float angulo=atan(dy/dx)*180/PI;
	int x,y;
  	if(angulo<45){//alguno < 45 en funcion de x
    	for (x = p1.x; x <= p2.x; ++x){
    		y = p1.y+m*(x-p1.x);
    		set_pixel(x,y);
    	}
  	}else{//alguno > 45 en funcion de y
    	for (y = p1.y; y <= p2.y; ++y){
		    x = (y-p1.y)/m + p1.x;
		    set_pixel(x,y);
  		}
  	}
}

void dda(point p1, point p2){ 
	double dx=(p2.x-p1.x);
	double dy=(p2.y-p1.y);
	double steps;
	float xInc,yInc,x=p1.x,y=p1.y;
	if(abs(dx)>abs(dy)){
		steps=(abs(dx));
	}
	else{
		steps=(abs(dy));
	}
	xInc=dx/(float)steps;
	yInc=dy/(float)steps;

	set_pixel(x,y);
	int k;
	for(k=0;k<steps;k++){
		x+=xInc;
		y+=yInc;
		set_pixel(round(x), round(y));
	}
}







//(2,3) -> (7,14)
void plot_main(){
	glClear(GL_COLOR_BUFFER_BIT);
	plano();//dibujar plano

	ln(point(60,90),point(70,10));
	dda(point(65,90),point(75,10));
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,50);//estableze posición de la ventana inicial
    glutInitWindowSize(400,400);//estableze tamaño de la ventana inicial
    glutCreateWindow("OpenGL");//label de la ventana

    init();
    glutDisplayFunc(plot_main); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
