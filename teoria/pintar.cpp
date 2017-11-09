//g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <iostream>
using namespace std;
void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,200.0,0.0,200.0);//establece una región de visualización
}

void lineSegment(void){
  glClear(GL_COLOR_BUFFER_BIT); //borrar búferes a valores predeterminados
  glColor3f(0,0,1); // cambia el color de la linea (RGB)
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex2i(180,15);
  glVertex2i(10,145);
  glEnd();
  glFlush();
}

void BoundaryFill4(int x, int y, color newcolor, color edgecolor){
  int current;
  current = Readpixel(x,y);
  if(current!=edgecolor && current!newcolor){
    BoundaryFill4(X+1);
  }
}





void main_plot(){
  lineSegment();

}



int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(400,300);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    glutDisplayFunc(main_plot); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
