// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>

class wcPt2D {
	public:
		GLfloat x, y;
};

void init (){
    glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-100.0, 100.0, -100.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void triangle (wcPt2D *verts){
	GLint k;
	glBegin (GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f (verts [k].x, verts [k].y);
	glEnd ( );
}

void displayFcn (void){
	int x0,y0;
 	int it=120;
 	x0=0;
 	y0=100;
 	glBegin(GL_POINTS);
 		glPointSize(20);              
		glVertex2i(x0+40,y0+ 50);     		
		glVertex2i(x0+40,y0+ 60);     		
		glVertex2i(x0+50,y0+ 60);
		glVertex2i(x0+50,y0+ 50);     		
   	glEnd();
	//posicion inicial del triagulo
	wcPt2D verts [3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0} };
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 1.0);
	glViewport (0, 0, 300, 300);//establece el visor izquierdo
	triangle (verts);
	//gira el triangulo y  lo visualiza en la mitad derecha
	glColor3f (1.0, 0.0, 0.0);
	glViewport (300, 0, 300, 300);
	glRotatef (90.0, 0.0, 0.0, 1.0);
	triangle (verts);
	glFlush ( );
}

int main (int argc, char ** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (600, 300);
	glutCreateWindow ("Split-Screen Example");
	init ( );
	glutDisplayFunc (displayFcn);
	glutMainLoop ( );
	return 0;
}