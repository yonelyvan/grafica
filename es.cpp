#include <GL/glut.h>
//Drawing funciton
void dibujar(){
  glClearColor(0,0,1,1); //Background color
  glClear(GL_COLOR_BUFFER_BIT ); //Draw order
  glFlush();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  //Simple buffer
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowPosition(50,25);
  glutInitWindowSize(320,180);
  glutCreateWindow("Green window");
  //Call to the drawing function
  glutDisplayFunc(dibujar);
  glutMainLoop();
  return 0;
}
