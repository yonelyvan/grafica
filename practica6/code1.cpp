//g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>  
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#define x first
#define y second
using namespace std;

typedef vector< vector< int > > M_patron;
typedef vector< vector< int > > vv_matriz;
typedef pair<int,int> point;

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

bool operator ==( Color oldColor, Color color){
	return ( color.r==oldColor.r && color.g==oldColor.g && color.b==oldColor.b )?true: false;
}

bool operator !=( Color oldColor, Color color){
	return (oldColor==color)?false: true;
}


void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,300.0,0.0,300.0);//establece una región de visualización
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

//patron
int mascara[8][8]={
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,1},
	{1,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,1,1},
	{1,0,1,0,0,0,1,1},
	{1,1,0,1,0,1,0,1},
	{1,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,1},
	};

//se obtiene el patron donde r indica que tan grande sera el patron 
M_patron get_patron(int r){
	if(r < 1){r=1;}
	M_patron P;
	for (int i = 0; i < 8; ++i){
		vector<int> Pi;
		for (int j = 0; j < 8; ++j){
			for (int k = 0; k < r; ++k){
				Pi.push_back(mascara[i][j]);
			}
		}
		for (int h = 0; h < r; ++h){
			P.push_back(Pi);
		}
	}
	return P;
}

//pintado de patron
void floodFill4_y(int x, int y, Color oldColor, Color newColor) {
	Color color;
	point point_i(x,y);
	queue<point> queue_points;
	queue_points.push(point_i);

	M_patron MMP= get_patron(4);
	int dim = MMP.size();
	map<int, map<int,bool> > visitados;
	while(!queue_points.empty()){
		point_i = queue_points.front();
		queue_points.pop();
		color = getPixelColor(point_i.x, point_i.y);
		if(color == oldColor && visitados[point_i.x][point_i.y]!=1){
			visitados[point_i.x][point_i.y]=1;
			if( MMP[point_i.x%dim][point_i.y%dim]==1 ){
				setPixelColor( point_i.x, point_i.y, newColor);
			}
			if(visitados[point_i.x+1][point_i.y]!=1){
				queue_points.push(point(point_i.x+1, point_i.y));
			}
			if(visitados[point_i.x][point_i.y+1]!=1){
				queue_points.push(point(point_i.x, point_i.y+1));
			}
			if(visitados[point_i.x][point_i.y-1]!=1){
				queue_points.push(point(point_i.x, point_i.y-1));
			}
			if(visitados[point_i.x-1][point_i.y]!=1){
				queue_points.push(point(point_i.x-1, point_i.y));
			}
		}
	}
}


void poligono(){
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0, 0.0, 0.0);
	int x0=10, y0=10;
	int zoom=6;

	glBegin(GL_LINES);
		glVertex2i(x0+0*zoom,y0+0*zoom);
		glVertex2i(x0+0*zoom,y0+21*zoom);
		glVertex2i(x0+0*zoom,y0+21*zoom);
		glVertex2i(x0+28*zoom,y0+21*zoom);
		glVertex2i(x0+28*zoom,y0+21*zoom);
		glVertex2i(x0+7*zoom,y0+0*zoom);
		glVertex2i(x0+7*zoom,y0+0*zoom);
		glVertex2i(x0+0*zoom,y0+0*zoom);
	glEnd();

	Color oldColor = {1.0, 1.0, 1.0};//blanco 	old
	Color newColor = {0.0, 1.0, 0.0};//verde 	new
	floodFill4_y(x0+10,y0+10,oldColor,newColor);
	glFlush(); 
}



int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(300,300);//estableze tamaño de la ventana inicial
    glutCreateWindow("OpenGL");//label de la ventana
    init();
    glutDisplayFunc(poligono); //visualizacion de una funion
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}