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

void line_y(point p1, point p2){//simple espejando en funcion de y 
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  int x,y;
  float m=(p2.y-p1.y)*1.0/(p2.x-p1.x); 
  for (y = p1.y; y <= p2.y; ++y){
    x = (y-p1.y)/m + p1.x;
    set_pixel(x,y);
    see_point(x,y);
  }
  glEnd();
  glFlush();
}

void line_y2(point p1, point p2){//simple espejando en funcion de  y 
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  int x,y;
  float m=(p2.y-p1.y)*1.0/(p2.x-p1.x); 
  for (y = p1.y; y <= p2.y; ++y){
    x = (y-p1.y)/m + p1.x;
    set_pixel(x,y);
    set_pixel(x+1,y);
    see_point(x,y);
  }
  glEnd();
  glFlush();
}

void line_xoy(point p1, point p2){ 
  float dy = p2.y-p1.y;
  float dx = p2.x-p1.x;
  float angulo=atan(dy/dx)*180/PI;
  see(angulo);
  if(angulo<45){//alguno < 45 en funcion de x
  cout<<"en funcion de X"<<endl;
    line_x(p1,p2);
  }else{//alguno > 45 en funcion de y
    cout<<"en funcion de Y"<<endl;
    line_y(p1,p2);
  }
}



void punto_medio_x(point p1,point p2){
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  float dx, dy, E, NE, d, x, y;
  dx = p2.x - p1.x;
  dy = p2.y - p1.y;
  d = 2.0 * dy-dx; //valor inicia para d
  E = 2.0 * dy; //incremento de E
  NE = 2.0 * (dy-dx); //incremento de NE
  x=p1.x;
  y=p1.y;
  set_pixel(x,y);
  see_point(x,y);
  while(x<p2.x){
    if(d<=0.0){//E
      d = d + E; 
      x = x + 0.001;
  }else{//NE
    d = d + NE;
    x = x + 0.001;
    y = y + 0.001;
  }
  set_pixel(x,y);
  see_point(x,y);
  }
}

void punto_medio_y(point p1,point p2){
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  float dx, dy, E, NE, d, x, y;
  dx = p2.x - p1.x;
  dy = p2.y - p1.y;
  d = 2.0 * dy-dx; //valor inicia para d
  E = 2.0 * dy; //incremento de E
  NE = 2.0 * (dy-dx); //incremento de NE
  x=p1.x;
  y=p1.y;
  set_pixel(x,y);
  see_point(x,y);
  //while(x<p2.x){
  while(y<p2.y){
    if(d<=0.0){//E
      d = d + E; 
      x = x + 0.001;
      y = y + 0.001;
  }else{//NE
    d = d + NE;
    x = x + 0.001;
    y = y + 0.001;
  }
  set_pixel(x,y);
  see_point(x,y);
  }
}


//(2,3) -> (7,14)
void plot_main(){
  point p1(2,3);
  point p2(42,84);//42,84
  //line_x(p1,p2);
  //line_y(p1,p2);
  //line_y2(p1,p2);
  //line_xoy(p1,p2);
  punto_medio_y(p1,p2);
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
