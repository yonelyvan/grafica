//g++ test.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
void init(){
  glClearColor(0.3,0.3,0.3,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,200.0,0.0,150.0);//establece una región de visualización
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



int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(400,300);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    glutDisplayFunc(lineSegment); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
}
