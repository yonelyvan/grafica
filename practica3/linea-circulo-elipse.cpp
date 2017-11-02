//g++ file.cpp -o m -lGL -lGLU -lglut && ./m
#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
#define see(x) cout<<#x<<" "<<x<<endl;
#define see_point(x,y) cout<<#x<<" "<<#y<<" : "<<x<<" "<<y<<endl;

#define PI 3.14159265
#define x first
#define y second
typedef pair<int,int> point;


int x_init=0, y_init=0;
int px=4;
int dim=120;


void init(){
  glClearColor(1,1,1,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,dim*px,0.0,dim*px);//establece una región de visualización
}


void plano(){
  //tablero
  glBegin(GL_LINES);
  glColor3f(0.85,0.85,0.85);
  //plano de 30x30
  for (int i = 0; i <= dim; ++i){
	//horizontales
	glVertex2i(x_init+ 0,y_init+ px*i);
	glVertex2i(x_init+ dim*px,y_init+ px*i);
	//verticales
	glVertex2i(x_init+ px*i,y_init+ 0);
	glVertex2i(x_init+ px*i,y_init+ dim*px);
  }
  glEnd();
  glFlush();
}


void set_pixel(int xi, int yi){
  glBegin(GL_POINTS);
  glColor3f(0,0,0);
  int x =x_init+ xi*px;
  int y =y_init+ yi*px;
  for (int i = 0; i < px; ++i){
	for (int j = 0; j < px; ++j){
	  glVertex2i(x+i, y+j);
	}
  }
  glEnd();
  glFlush();
}

void set_pixel(point p){
  glBegin(GL_POINTS);
  glColor3f(0,0,0);
  int x =x_init+ p.x*px;
  int y =y_init+ p.y*px;
  for (int i = 0; i < px; ++i){
	for (int j = 0; j < px; ++j){
	  glVertex2i(x+i, y+j);
	}
  }
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


/* Algoritmo de dibujo de líneas de Bresenham para |m| < 1.0. */
void bresenham (point p1, point p2){
	int dx = fabs (p2.x - p1.x), dy = fabs(p2.y - p1.y);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	// Determinar qué extremo usar como posición inicial.
	if (p1.x > p2.x) {
		x = p2.x;
		y = p2.y;
		p2.x = p1.x;
	}
	else {
		x = p1.x;
		y = p1.y;
	}
	set_pixel(x, y);
	while (x < p2.x) {
		x++;
		if (p < 0)
			p += twoDy;
		else {
			y++;
			p += twoDyMinusDx;
		}
		set_pixel(x, y);
	}
}

void bresenham_(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		set_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			set_pixel(x, y);
		}

	} else {
		set_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			set_pixel(x, y);
		}
	}
}


void plot_circle_point(point pc, point pk){
	set_pixel( pc.x + pk.x,  pc.y + pk.y);
	set_pixel( pc.x - pk.x,  pc.y + pk.y);
	set_pixel( pc.x + pk.x,  pc.y - pk.y);
	set_pixel( pc.x - pk.x,  pc.y - pk.y);
	set_pixel( pc.x + pk.y,  pc.y + pk.x);
	set_pixel( pc.x - pk.y,  pc.y + pk.x);
	set_pixel( pc.x + pk.y,  pc.y - pk.x);
	set_pixel( pc.x - pk.y,  pc.y - pk.x);
}

void plot_elipse_point(point pc, point pk){
	set_pixel( pc.x + pk.x,  pc.y + pk.y);
	set_pixel( pc.x - pk.x,  pc.y + pk.y);
	set_pixel( pc.x + pk.x,  pc.y - pk.y);
	set_pixel( pc.x - pk.x,  pc.y - pk.y);
}

void circulo_punto_medio(point pc, int r){
	int x, y, p;
	x = 0;
	y = r;
	p = 1-r;
	plot_circle_point(pc,point(x,y)); 
	//para un octante
	while (x < y){//x < y
		++x;
		if(p < 0)
			p += 2*x + 1;
		else{
			--y;
			p += 2*(x-y) + 1;
		}
		plot_circle_point(pc, point(x,y));
	}
}

void elipse(point pc, int rx, int ry){
	int x, y, p, px, py;
	int rx2, ry2, tworx2, twory2;
	ry2 = ry*ry;
	rx2 = rx*rx;
	twory2 = 2 * ry2;
	tworx2 = 2 * rx2;
	// región 1 
	x = 0;
	y = ry;
	plot_elipse_point(pc, point(x,y));
	p = round(ry2 - rx2*ry + 0.25*rx2);
	px = 0;
	py = tworx2*y;
	while (px < py){ // se cicla hasta trazar la región 1
		x = x + 1;
		px = px + twory2;
		if (p < 0)
		  	p = p + ry2 + px;
		else {
			y = y - 1;
			py = py - tworx2;
			p = p + ry2 + px - py;
		}
		plot_elipse_point(pc, point(x,y));
	}
	//region 2
	p = round(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2);
	px = 0;
	py = tworx2*y;
	while (y > 0){ // se cicla hasta trazar la región 2
		y = y - 1;
		py = py - tworx2;
		if (p > 0)
		  	p = p + rx2 - py;
		else {
		  	x = x + 1;
		  	px = px + twory2;
		  	p = p + rx2 + py + px;
		}
		plot_elipse_point(pc, point(x,y));
	}
}

void plot_elipse_mitad_point(point pc, point pk){
	set_pixel( pc.x + pk.x,  pc.y - pk.y);
	set_pixel( pc.x - pk.x,  pc.y - pk.y);
}

void elipse_mitad(point pc, int rx, int ry){
	int x, y, p, px, py;
	int rx2, ry2, tworx2, twory2;
	ry2 = ry*ry;
	rx2 = rx*rx;
	twory2 = 2 * ry2;
	tworx2 = 2 * rx2;
	// región 1 
	x = 0;
	y = ry;
	plot_elipse_mitad_point(pc, point(x,y));
	p = round(ry2 - rx2*ry + 0.25*rx2);
	px = 0;
	py = tworx2*y;
	while (px < py){ // se cicla hasta trazar la región 1
		x = x + 1;
		px = px + twory2;
		if (p < 0)
		  	p = p + ry2 + px;
		else {
			y = y - 1;
			py = py - tworx2;
			p = p + ry2 + px - py;
		}
		plot_elipse_mitad_point(pc, point(x,y));
	}
	//region 2
	p = round(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2);
	px = 0;
	py = tworx2*y;
	while (y > 0){ // se cicla hasta trazar la región 2
		y = y - 1;
		py = py - tworx2;
		if (p > 0)
		  	p = p + rx2 - py;
		else {
		  	x = x + 1;
		  	px = px + twory2;
		  	p = p + rx2 + py + px;
		}
		plot_elipse_mitad_point(pc, point(x,y));
	}
}


void estrella (float cx, float cy, float radius){
	circulo_punto_medio( point(cx,cy),radius);//dibujar circulo
    const float to_radians=3.14159/180;
    glColor3f(1.0,0.0,0.0);
    int count = 1;//para verificar si es extremo de la estrella o no
    point p_temp = point(cx + cos(0) * radius, cy + sin(0) * radius); 
    point p_new;
    float flag;
    for (int i=0; i<=360; i+=36){
        float angulo = i * to_radians;
        if(count%2!=0){ //extremos de la estrella
        	p_new=point(cx + cos (angulo) * radius, cy + sin (angulo) * radius);
        }
        else{ //puntos internos
        	p_new=point((cx + cos (angulo) * radius/2), (cy + sin (angulo) * radius/2));	
    	}
        dda(p_temp, p_new);
    	p_temp=p_new;
    	count++;
    }
}

void rana(point pc, int rx, int ry){
	elipse(pc,rx,ry);
	circulo_punto_medio(point(pc.x+rx, pc.y+ry),rx/3);
	circulo_punto_medio(point(pc.x-rx, pc.y+ry),rx/3);
	circulo_punto_medio(point(pc.x+rx, pc.y+ry),rx/5);
	circulo_punto_medio(point(pc.x-rx, pc.y+ry),rx/5);
	elipse_mitad(pc,rx/2,ry/2);
	dda(point(pc.x-rx/2,pc.y),point(pc.x+rx/2,pc.y));
}




//(2,3) -> (42,84)
void plot_main(){
	glClear(GL_COLOR_BUFFER_BIT);
	plano();//dibujar plano
	point p1(2,3); //20, 10) y (30, 18
	point p2(42,84); //42,84
	//dda(p1,p2);
	//bresenham(p1, p2);
	//circulo_punto_medio( point(50,50),40);
	//elipse(point(50,50),20,40);
	//estrella(point(50,50),40);
	//estrella(50,50,40);
	rana(point(60,60),40,20);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv); //se inicializa GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
	glutInitWindowPosition(50,50);//estableze posición de la ventana inicial
	glutInitWindowSize(dim*px,dim*px);//estableze tamaño de la ventana inicial
	glutCreateWindow("OpenGL");//label de la ventana

	init();
	glutDisplayFunc(plot_main); //visualizacion de una funion
	glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
	exit(0);
}
