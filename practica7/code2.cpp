// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>


class wcPt2D {
	public:
		GLfloat x, y;
};

void init (){
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-300.0, 300.0, -300.0, 300.0);
	glMatrixMode (GL_MODELVIEW);
}

void triangle (wcPt2D *verts){
	GLint k;
	glBegin (GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f (verts [k].x, verts [k].y);
	glEnd ( );
}

void displayFcn (){
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
void displayFcn2(){
	glClear(GL_COLOR_BUFFER_BIT);   
 	//glColor3f(0,0,1);
 	

	glMatrixMode (GL_MODELVIEW);

	glViewport (300, 300, 200, 200);
	glColor3f (0.0, 0.0, 1.0);
	glRecti (50, 100, 200, 150); // Muestra un rectángulo azul.
	glColor3f (1.0, 0.0, 0.0);
	
	glViewport (280, 300, 200, 200);
	glTranslatef (-200.0, -50.0, 0.0); // Establece los parámetros de traslación.
	glRecti (50, 100, 200, 150); // Muestra un rectángulo rojo trasladado.
	/*
	
	glLoadIdentity ( ); // Carga la matriz identidad como matriz actual.
	
	glRotatef (90.0, 0.0, 0.0, 1.0); // Establece una rotación de 90 grados alrededor
	// del eje z .
	glRecti (50, 100, 200, 150); // Muestra un rectángulo rojo girado.
	glLoadIdentity ( ); // Carga la matriz identidad como matriz actual.
	glScalef (-0.5, 1.0, 1.0); // Establece los parámetros de reflexión y escala.
	glRecti (50, 100, 200, 150); // Muestra un rectángulo rojo transformado.
	*/
	glFlush ( );
}


int main (int argc, char ** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (600, 600);
	glutCreateWindow ("Split-Screen Example");
	init ( );
	//glutDisplayFunc (displayFcn);
	glutDisplayFunc (displayFcn2);
	glutMainLoop ( );
	return 0;
}