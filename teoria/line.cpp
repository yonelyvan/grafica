//g++ line.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <iostream>
using namespace std;
#define see(x) cout<<#x<<" "<<x<<endl;
#define see_point(x,y) cout<<#x<<" "<<#y<<" : "<<x<<" "<<y<<endl;

void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,200.0,0.0,200.0);//establece una región de visualización
}

int x_init=10, y_init=10;
int px=10;
int dim=18;

void plano(){
  //tablero
  glBegin(GL_LINES);
  glColor3f(0,0,0);
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

//dibujar desde (2,3) -> (7,14)
void line_x(){//simple espejando x 
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  int x,y;
  for (x = 2; x <= 7; ++x){
    y = (11*x-7)/5;
    set_pixel(x,y);
    see_point(x,y);
  }
}

//dibujar desde (2,3) -> (7,14)
void line_y(){//simple espejando y 
  glClear(GL_COLOR_BUFFER_BIT);
  plano();//dibujar plano
  int x,y;
  for (y = 3; y <= 14; ++y){
    x = (5*y+7)/11;
    set_pixel(x,y);
    see_point(x,y);
  }
}




int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(400,400);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    glutDisplayFunc(line_y); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
