//g++ file.cpp -o m -lGL -lGLU -lglut
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#define x first
#define y second


typedef pair<int,int> point;

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

bool operator ==( Color oldColor, Color color){
	return ( color.r==oldColor.r && color.g==oldColor.g && color.b==oldColor.b )?true: false;
}

void set_pixel(int xi, int yi){
  	glBegin(GL_POINTS);
  	glColor3f(0,0,0);
	glVertex2i(xi, yi);
  	glEnd();
  	glFlush();
}


void dda(point p1, point p2){ 
	double dx=(p2.x-p1.x);
	double dy=(p2.y-p1.y);
	double steps;
	float xInc,yInc,x=p1.x,y=p1.y;
	if(abs(dx)>abs(dy)){
		steps=(abs(dx));
	}
	else{
		steps=(abs(dy));
	}
	xInc=dx/(float)steps;
	yInc=dy/(float)steps;

	set_pixel(x,y);
	int k;
	for(k=0;k<steps;k++){
		x+=xInc;
		y+=yInc;
		set_pixel(round(x), round(y));
	}
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(int x, int y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(int x, int y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(int x, int y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color == oldColor){
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

void onMouseClick(int button, int state, int x, int y){
	Color newColor = {0.0f, 1.0f, 0.0f};
	Color oldColor = {1.0f, 1.0f, 1.0f};
	floodFill(101, 199, oldColor, newColor);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	point p1 = point(100, 100), // bottom-right
		p2 = point(200, 100), // bottom-left
		p3 = point(200, 200), // top-right
		p4 = point(100, 200); // top-left
	
	dda(p1, p2);
	dda(p2, p3);
	dda(p3, p4);
	dda(p4, p1);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}