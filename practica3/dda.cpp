//g++ dda.cpp -o m -lGL -lGLU -lglut
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
void line_x(point p1, point p2){//simple espejando en funcion de x 
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  int x,y;
  float m=( p2.y-p1.y )*1.0/( p2.x-p1.x );//pendiente 
  see(m);
  for (x = p1.x; x <= p2.x; ++x){
    y = p1.y+m*(x-p1.x);
    set_pixel(x,y);
    see_point(x,y);
  }
  glEnd();
  glFlush();
}

void dda(point p1, point p2){
    glClear(GL_COLOR_BUFFER_BIT);
    plano();//dibujar plano
    int dx,dy,xinc,yinc,x,y, steps;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    see(dx);
    if( abs(dx) > abs(dy) ){
        steps=abs(dx);
    }
        steps=abs(dx);
    xinc = dx/steps;
    yinc = dy/steps;
    x=p1.x;
    y=p2.y;
    set_pixel(round(x),round(y));
    see(steps);
    for (int i = 0; i < steps; ++i){
        x=x+xinc;
        y=y+yinc;
        set_pixel(round(x),round(y));
    }
}









//(2,3) -> (7,14)
void plot_main(){
  point p1(2,3);
  point p2(42,84);//42,84
  //line_x(p1,p2);
  dda(p1,p2);
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
