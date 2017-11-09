g++ practica2.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>  
 
void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,600.0,0.0,200.0);//establece una región de visualización
}

void main_plot() {
   	glClear(GL_COLOR_BUFFER_BIT);   
 	glColor3f(0,0,1);
 	int x0,y0;
 	x0=0;
 	y0=100;
 	glBegin(GL_POINTS);
 		glPointSize(20);              
		glVertex2i(x0+5,y0+ 50);     		
		glVertex2i(x0+5,y0+ 60);     		
		glVertex2i(x0+10,y0+ 60);
		glVertex2i(x0+10,y0+ 50);     		
   	glEnd();

   	x0=50;
 	y0=100;
	glBegin(GL_LINES);
		glVertex2i(x0+10,y0+10);
		glVertex2i(x0+30,y0+60);
		glVertex2i(x0+20,y0+10);
		glVertex2i(x0+60,y0+85);
	glEnd();

	x0=100;
 	y0=100;
	glBegin(GL_LINE_STRIP);
		glVertex2i(x0+60,y0+10);
		glVertex2i(x0+80,y0+60);
		glVertex2i(x0+70,y0+10);
		glVertex2i(x0+110,y0+85);
		glVertex2i(x0+40,y0+40);
	glEnd();

	x0=200;
 	y0=100;
	glBegin(GL_LINE_LOOP);
		glVertex2i(x0+60,y0+10);
		glVertex2i(x0+80,y0+60);
		glVertex2i(x0+70,y0+10);
		glVertex2i(x0+110,y0+85);
		glVertex2i(x0+40,y0+40);
	glEnd();

	x0=300;
 	y0=100;
	glBegin(GL_POLYGON);
		glVertex2i(x0+10,y0+10);
		glVertex2i(x0+50,y0+10);
		glVertex2i(x0+10,y0+50);
		glVertex2i(x0+110,y0+85);
		glVertex2i(x0+40,y0+40);
		glVertex2i(x0+40,y0+40);
	glEnd();

	x0=0;
 	y0=0;
	glBegin(GL_TRIANGLES);          
    	glVertex2i(x0+10,y0+10);
		glVertex2i(x0+10,y0+50);
		glVertex2i(x0+50,y0+10);

   glEnd();


   glFlush();  
}
 

int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(600,200);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    glutDisplayFunc(main_plot); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
