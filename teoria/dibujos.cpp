//g++ file.cpp -o m -lGL -lGLU -lglut
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


/*dibujando lineas*/
void ln(point p1, point p2){
  	float dy = p2.y-p1.y;
  	float dx = p2.x-p1.x;
	if( fabs(dx)> fabs(dy)){
		if(p1.x>p2.x)
			swap(p1,p2);
	}else{
		if(p1.y>p2.y) 
			swap(p1,p2);
	}
	float m=dy/dx;//pendiente 
	int x,y;
  	if( fabs(dx)>fabs(dy) ){//en funcion de x
    	for (x = p1.x; x < p2.x; ++x){
    		y = p1.y+m*(x-p1.x);
    		set_pixel(x,y);
    	}
  	}else{//alguno > 45 en funcion de y
    	for (y = p1.y; y < p2.y; ++y){
		    x = (y-p1.y)/m + p1.x;
		    set_pixel(x,y);
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

void circulo(point pc, int r){
	for (int i = 0; i < 45; ++i){
		plot_circle_point(pc,point( r*cos(i*PI/180), r*sin(i*PI/180) )); 	
	}
}


void estrella (float cx, float cy, float radius){
	circulo( point(cx,cy),radius);//dibujar circulo
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
        //dda(p_temp, p_new);
        ln(p_temp, p_new);
    	p_temp=p_new;
    	count++;
    }
}

void plot_elipse_point(point pc, point pk){
	set_pixel( pc.x + pk.x,  pc.y + pk.y);
	set_pixel( pc.x - pk.x,  pc.y + pk.y);
	set_pixel( pc.x + pk.x,  pc.y - pk.y);
	set_pixel( pc.x - pk.x,  pc.y - pk.y);
}


void plot_elipse_mitad_point(point pc, point pk){
	set_pixel( pc.x + pk.x,  pc.y - pk.y);
	set_pixel( pc.x - pk.x,  pc.y - pk.y);
}

void elipse(point pc, int rx, int ry){
	for (int i = 0; i < 90; ++i){
		plot_elipse_point(pc,point( rx*cos(i*PI/180), ry*sin(i*PI/180) )); 	
	}
}


void elipse_mitad(point pc, int rx, int ry){
	for (int i = 0; i < 90; ++i){
		plot_elipse_mitad_point(pc,point( rx*cos(i*PI/180), ry*sin(i*PI/180) )); 	
	}
}

void rana(point pc, int rx, int ry){
	elipse(pc,rx,ry);
	circulo(point(pc.x+rx, pc.y+ry),rx/3);
	circulo(point(pc.x-rx, pc.y+ry),rx/3);
	circulo(point(pc.x+rx, pc.y+ry),rx/5);
	circulo(point(pc.x-rx, pc.y+ry),rx/5);
	elipse_mitad(pc,rx/2,ry/2);
	ln(point(pc.x-rx/2,pc.y),point(pc.x+rx/2,pc.y));
}





//(2,3) -> (7,14)
void plot_main(){
	glClear(GL_COLOR_BUFFER_BIT);
	plano();//dibujar plano

	//ln(point(10,10),point(70,70));
	//dda(point(15,10),point(75,70));
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
