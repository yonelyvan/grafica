// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define PI 3.1415
using namespace std;


GLfloat color[8][3] ={
	{ 0.0,0.0,0.0 },
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,0.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 0.0,1.0,1.0 },
};



void cilindro (int r){
	GLfloat x,y,z;
	//referencia el origen de coordenadas
	glBegin(GL_QUAD_STRIP);
	glColor3fv(color[3]);
	for (int i = 0; i < 361; ++i){
		x = r*cos(i*PI/180); 
		y = r*sin(i*PI/180); 	
		z = 1.0;
		GLfloat p[3]={x,y,z};
		GLfloat p2[3]={x,y,-z};
		glVertex3fv(p);
		glVertex3fv(p2);

	}
	glEnd();
	//tap superior
	glColor3fv(color[4]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 361; ++i){
		x = r*cos(i*PI/180); 
		y = r*sin(i*PI/180); 	
		z = 1.0;
		GLfloat p[3]={x,y,z};
		glVertex3fv(p);
	}
	glEnd();
	//tapa inferior
	glColor3fv(color[5]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 361; ++i){
		x = r*cos(i*PI/180); 
		y = r*sin(i*PI/180); 	
		z = -1.0;
		GLfloat p[3]={x,y,z};
		glVertex3fv(p);
	}
	glEnd();
}




void colorcube(){
	cilindro(1);
} 

double rotate_y = 0;
double rotate_x = 0;

void specialKeys(int key, int x, int y){
	if (key == GLUT_KEY_RIGHT)
		rotate_y +=5;
	else if (key == GLUT_KEY_LEFT)
		rotate_y -=5;
	else if (key == GLUT_KEY_UP)
		rotate_x +=5;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -=5;
	glutPostRedisplay();
}

void display(){
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	//gluPerspective(60, w / h, 0.1, 100);
	glOrtho(-3.0f, 2.5f, -3.0f, 2.5f, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		3, 3, 3,
		0, 0, 0,
		0, 0, 1
	);

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	colorcube();

	glutSwapBuffers();
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("GLUT");
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}