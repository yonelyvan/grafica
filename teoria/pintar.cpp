//g++ file.cpp -o m -lGL -lGLU -lglut
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
#define x first
#define y second
#define INF 999999


typedef pair<int,int> point;

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};


int windowWidth;
int windowHeight;
int x_mouse_f;
int y_mouse_f;

bool operator ==( Color oldColor, Color color){
	return ( color.r==oldColor.r && color.g==oldColor.g && color.b==oldColor.b )?true: false;
}

bool operator !=( Color oldColor, Color color){
	return (oldColor==color)?false: true;
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


void plot_cuadrado(point p1, point p2){ 
  	int dy=p2.y-p1.y;
	int dx=p2.x-p1.x;
	//cuadrantes
	int cx = dx>0?1:-1;
	int cy = dy>0?1:-1;

	int lmin=min(abs(dx), abs(dy));
	dda(p1,point( p1.x+lmin*cx, p1.y ));
	dda(p1,point(p1.x,p1.y+lmin*cy));
	dda(point(p1.x+lmin*cx, p1.y),point(p1.x+lmin*cx, p1.y+lmin*cy));
	dda(point(p1.x, p1.y+lmin*cy),point(p1.x+lmin*cx, p1.y+lmin*cy));	
}

void BoundaryFill4(int x, int y, Color fillColor, Color edgecolor) {
	Color currentColor = getPixelColor(x, y);
	if( (currentColor!= fillColor)&&(currentColor!= edgecolor) ) {
		setPixelColor(x, y, fillColor);
		BoundaryFill4(x+1, y, fillColor, edgecolor);
		BoundaryFill4(x-1, y, fillColor, edgecolor);
		BoundaryFill4(x, y+1, fillColor, edgecolor);
		BoundaryFill4(x, y-1, fillColor, edgecolor);
	}
	return;
}

void BoundaryFill4_y(int x, int y, Color fillColor, Color edgecolor) {
	Color currentColor;
	point point_i(x,y);
	queue<point> queue_points;
	queue_points.push(point(x, y));

	while( !queue_points.empty() ){
		point_i = queue_points.front();
		queue_points.pop();
		currentColor = getPixelColor(point_i.x, point_i.y);
		if( (currentColor!= fillColor)&&(currentColor!= edgecolor) ) {
			setPixelColor(point_i.x, point_i.y, fillColor);
			queue_points.push(point(point_i.x+1, point_i.y));
			queue_points.push(point(point_i.x-1, point_i.y));
			queue_points.push(point(point_i.x, point_i.y+1));
			queue_points.push(point(point_i.x, point_i.y-1));
		}
	}
		
}

void floodFill4(int x, int y, Color oldColor, Color newColor) {
	Color color = getPixelColor(x, y);
	if(color == oldColor){
		setPixelColor(x, y, newColor);
		floodFill4(x+1, y, oldColor, newColor);
		floodFill4(x, y+1, oldColor, newColor);
		floodFill4(x-1, y, oldColor, newColor);
		floodFill4(x, y-1, oldColor, newColor);
	}
	return;
}

void floodFill4_y(int x, int y, Color oldColor, Color newColor) {
	cout<<x<<" "<<y<<endl;
	Color color;
	point point_i(x,y);
	queue<point> queue_points;
	queue_points.push(point_i);
	while(!queue_points.empty()){
		point_i = queue_points.front();
		queue_points.pop();
		color = getPixelColor(point_i.x, point_i.y);
		if(color == oldColor){
			setPixelColor( point_i.x, point_i.y, newColor);
			queue_points.push(point(point_i.x+1, point_i.y));
			queue_points.push(point(point_i.x, point_i.y+1));
			queue_points.push(point(point_i.x-1, point_i.y));
			queue_points.push(point(point_i.x, point_i.y-1));
		}
	}
}


/*
void scan_line(int x, int y, Color newColor, Color edgecolor) {
	int xt, xi, xf, x_min, x_max;
	int yt, yi, yf, y_min, y_max;

	Color color;
	x_min=INF;
	y_min=INF;
	x_max=-INF;
	y_max=-INF;

	color = getPixelColor(x, y);
	while(color!=edgecolor && color!=newColor){
		setPixelColor( x, y, newColor);
		++y;
		color = getPixelColor(x, y);
	}
	point point_i(x,y);
	queue<point> queue_points;
	queue_points.push(point_i);
	while(!queue_points.empty()){
		point_i = queue_points.front();
		queue_points.pop();
		color = getPixelColor(point_i.x, point_i.y);
		if(color == edgecolor){
			x_min=min(x_min,point_i.x);
			x_max=max(x_max,point_i.x);
			y_min=min(y_min,point_i.y);
			y_max=max(y_max,point_i.y);
			setPixelColor( point_i.x, point_i.y, newColor);
			queue_points.push(point(point_i.x+1, point_i.y));
			queue_points.push(point(point_i.x, point_i.y+1));
			queue_points.push(point(point_i.x-1, point_i.y));
			queue_points.push(point(point_i.x, point_i.y-1));
		}
	}
	cout<<"X ["<<x_min<<" - "<<x_max<<"]"<<endl;
	cout<<"Y ["<<y_min<<" - "<<y_max<<"]"<<endl;

	int par=0;
	point point_init,point_end;
	for (int i = x_min; i < x_max; ++i){
		for (int j = y_min; j < y_max; ++j){
			color = getPixelColor(i, j);
			if(color == edgecolor){
				point_init=point(i,j);
				++par;
			}
			if(par){
				cout<<"pintando"<<endl;
				point_end=point(i,j);
				dda(point_init,point_end);
				par=0;
			}
		}
	}
}
*/

// funcion que controla el redimensionamiento de la ventana
void resize(GLsizei w, GLsizei h){
    //actualiza los valores globales de tamano de ventana
    windowWidth = w;
    windowHeight = h;

    //pantalla completa
    glViewport(0, 0, w, h);

    //iniciar matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //configurar la proyeccion ortogonal
    glOrtho(0, w, 0, h, 1.f, -1.f);
    printf("resize: nuevo tamano de ventana: %dx%d\n", w, h);

    //Activa matriz del modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onMouseClick(int button, int state, int x, int y){
	Color newColor = {0.0, 1.0, 0.0};//verde 	new
	Color oldColor = {1.0, 1.0, 1.0};//blanco 	old
	Color edgecolor = {0.0, 0.0, 0.0};//negro	frontera
    x_mouse_f = x;
    y_mouse_f = windowHeight - y;
	
	//BoundaryFill4(x_mouse_f, y_mouse_f, newColor, edgecolor);
	//BoundaryFill4_y(x_mouse_f, y_mouse_f, newColor, edgecolor);
	
	//floodFill4(x_mouse_f, y_mouse_f, oldColor, newColor);
	//floodFill4_y(x_mouse_f, y_mouse_f, oldColor, newColor);

	scan_line(x_mouse_f, y_mouse_f, newColor, edgecolor);
}



void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	int x0,y0;
	point p1,p2;
	
	x0=10,y0=10;
	p1=point(x0+0, y0+0);
	p2=point(x0+50, y0+50);
	plot_cuadrado(p1,p2);
	
	x0=70,y0=10;
	p1=point(x0+0, y0+0);
	p2=point(x0+100, y0+100);
	plot_cuadrado(p1,p2);


	x0=200,y0=10;
	p1=point(x0+0, y0+0);
	p2=point(x0+400, y0+400);
	plot_cuadrado(p1,p2);

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	// CALLBACK accion de redimensionamiento de la pantalla
    glutReshapeFunc (resize); 
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}