// g++ file.cpp -o m -lGL -lGLU -lglut
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#define PI 3.14159265
#define x first
#define y second

typedef pair<int,int> point;

// ******* Seccion de variables globales ****************
// dimensiones de la pantalla
int windowWidth;
int windowHeight;
// variables de control del puntero
int xi, xf, xt;
int yi, yf, yt;
// ******************************************************
// Configuracion inicial del programa
int init (void){
    // color usado al limpiar la ventana
    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
}

/********************** menu ***************/
int iFondo = 0; //fondo por defecto
int ifigura =3; //figura por defecto
// coleccion de constantes para determinar los colores a usar
typedef enum {FONDO1,FONDO2,FONDO3,LINEA,CIRCULO,CUADRADO,ELIPSE} opcionesmenu;

void onMenu(int opcion){
    switch(opcion){
        case FONDO1: iFondo = 0; break;
        case FONDO2: iFondo = 1; break;
        case FONDO3: iFondo = 2; break;
        case LINEA: ifigura = 3; break;
        case CIRCULO: ifigura = 4; break;
        case CUADRADO: ifigura = 5; break;
        case ELIPSE: ifigura = 6; break;
    }
    glutPostRedisplay();
}

void creacionMenu(void){
    int menuFondo, menuDibujo, menufigura, menuPrincipal;

    // glutAddMenuEntry genera una opcion para seleccionar
    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Negro", FONDO1);
    glutAddMenuEntry("Verde oscuro", FONDO2);
    glutAddMenuEntry("Azul oscuro", FONDO3);

    menufigura = glutCreateMenu(onMenu);
    glutAddMenuEntry("linea", LINEA);
    glutAddMenuEntry("circulo", CIRCULO);
    glutAddMenuEntry("cuadrado", CUADRADO);
    glutAddMenuEntry("elipse", ELIPSE);

    // asocian los respectivos submenus
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Color de fondo", menuFondo);
    glutAddSubMenu("figura", menufigura);

    // se dispone al clic derecho para ejecutar el menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/************************************************/


/******************** DIBUJOS RECTA CIRCULO ELIPSE CUADRADO **********************/
void set_pixel(int xi, int yi){
  	glBegin(GL_POINTS);
  	glColor3f(0,0,0);
	glVertex2i(xi, yi);
  	glEnd();
  	glFlush();
}

//funcion cuadrado
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

void recta(point p1, point p2){ 
	dda(p1,p2);
}

int min(int a, int b){
	return a<b?a:b;
}

void cuadrado(point p1, point p2){ 
  	int dy=p2.y-p1.y;
	int dx=p2.x-p1.x;
	//cuadrantes
	int cx = dx>0?1:-1;
	int cy = dy>0?1:-1;

	int lmin=min(abs(dx), abs(dy));
	cout<<"DX "<<dx<<" DY "<<dy<<" LMIN "<<lmin<<endl;  
	recta(p1,point( p1.x+lmin*cx, p1.y ));
	recta(p1,point(p1.x,p1.y+lmin*cy));
	recta(point(p1.x+lmin*cx, p1.y),point(p1.x+lmin*cx, p1.y+lmin*cy));
	recta(point(p1.x, p1.y+lmin*cy),point(p1.x+lmin*cx, p1.y+lmin*cy));	
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

void circulo(point pc, int r){
	int x, y, p;
	x = 0;
	y = r;
	p = 1-r;
	plot_circle_point(pc,point(x,y)); 
	//para un octante
	while (x < y){
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

void main_plot(int xi,int yi, int xf,int yf, int figura){
	int dy=yf-yi;
	int dx=xf-xi;
	if(abs(dx)>0 && abs(dy)>0){
        switch(figura){
            case LINEA: 
                recta(point(xi,yi),point(xf,yf));
                break;
            case CIRCULO: 
    	        circulo(point(xi+dx/2,yi+dy/2),min(abs(dx),abs(dy))/2 );
                break;
            case CUADRADO: 
                cuadrado(point(xi,yi),point(xf,yf)); 
                break;
            
            case ELIPSE: 
                elipse(point(xi+dx/2,yi+dy/2),abs(dx)/2,abs(dy)/2 );
                break;
        }        
	}
}
/************************************************/




// funcion principal de despliegue
void display(void){
    int i;
    //limpiar pantalla
    glClear(GL_COLOR_BUFFER_BIT);
    //pinta rectangulo gris con el  arrastre
    glColor3ub(192,192,192);
    glBegin(GL_POINTS);
    for (i=xi ; i<=xf ; i++)
        glVertex2i(i,yi), glVertex2i(i,yf);
    for (i=yi ; i<=yf ; i++)
        glVertex2i(xi,i), glVertex2i(xf,i);
    for (i=xi ; i>=xf ; i--)
        glVertex2i(i,yi), glVertex2i(i,yf);
    for (i=yi ; i>=yf ; i--)
        glVertex2i(xi,i), glVertex2i(xf,i);
    glEnd();
    
    /*************************  MENU *************************/
    float colores[6][3] = {
        {1.00f, 1.00f, 1.00f}, // 0 - blanco
        {0.06f, 0.25f, 0.13f}, // 1 - verde osucro
        {0.20f, 0.14f, 0.66f}, // 3 - azul claro
    };
    //actualizar color de fondo
    glClearColor(colores[iFondo][0], colores[iFondo][1], colores[iFondo][2], 1.0f);
    glFlush();
    //actualizar figuira
    main_plot(xi,yi,xf,yf, ifigura);
    /*******************************************************/
    // activa el pintado de pixeles
    glBegin(GL_POINTS);

    // pinta posicion del mouse cada 2 segundos con pixeles
    glColor3ub(228, 0, 0);
    for(i=-10; i<=10; i++)
        glVertex2i(xt+i,yt+i), glVertex2i(xt+i,yt-i);
    
    // pinta donde hace clic en verde
    glColor3ub(0, 228, 0);
    for(i=-10; i<=10; i++)
        glVertex2i(xi+i,yi), glVertex2i(xi,yi+i);

    // termina el pintado de pixeles
    glEnd();

    // pintado instantaneo de la escena
    glutSwapBuffers();
}

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

// captura el movimiento pasivo del raton
void mouse_move(int x, int y){
    // captura la posicion del puntero todo el tiempo
    xt = x;
    yt = windowHeight - y;
    glutPostRedisplay();
}

// captura el movimiento pasivo del raton
void mouse_drag(int x, int y){
    xf = x;
    yf = windowHeight - y;
    // manda a ppintar (metodo display)
    glutPostRedisplay();
}

typedef GLubyte Color[3];

void getPixel(int x, int y, Color rgb){
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb);
}





// captura el evento de clic
void mouse_click(int button, int state, int x, int y){
    Color c;
    if(state == GLUT_DOWN){
        // captura posicion inicial de arrastre
        xi = x;
        yi = windowHeight - y;
        xf = xi;
        yf = yi;
        // captura el color del pixel sobre puntero y lo imprime
        // glReadnPixels(xi, yi, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, c);
        getPixel(xi, yi, c);
        printf("posicion inicial: %d, %d, color(%3d,%3d,%3d)\n",xi, yi, c[0], c[1], c[2]);
    }
    if(state == GLUT_UP){
        // captura posicion inicial de arranque
        printf("mouse_click: Arrastre con el boton %d hasta %3d, %3d\n",button, xf, yf);
    }
    // manda a ppintar (metodo display)
    glutPostRedisplay();
}

// captura del teclado, teclas normales
void normal_key(GLubyte key,int x, int y){
    // termina el programa con la tecla ESC
    char s[80] = "";
    if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) sprintf(s, "%s SHIFT ", s);
    if(glutGetModifiers() & GLUT_ACTIVE_CTRL) sprintf(s, "%s CTRL ", s);
    if(glutGetModifiers() & GLUT_ACTIVE_ALT) sprintf(s, "%s ALT ", s);

    if (key >= 32 && key <= 128)
        printf("normal key: '%c' dec:%d %s\n", key, key, s);
    else
        printf("normal key: dec:%d %s\n", key, s);
    
    if(key == '?'){
        printf("ACTIVE = %d\n", glutGameModeGet(GLUT_GAME_MODE_ACTIVE));
        printf("POSSIBLE = %d\n", glutGameModeGet(GLUT_GAME_MODE_POSSIBLE));
        printf("WIDTH = %d\n", glutGameModeGet(GLUT_GAME_MODE_WIDTH));
        printf("HEIGHT = %d\n", glutGameModeGet(GLUT_GAME_MODE_HEIGHT));
        printf("PIXEL DEPTH = %d\n", glutGameModeGet(GLUT_GAME_MODE_PIXEL_DEPTH));
        printf("REFRESH RATE = %d\n", glutGameModeGet(GLUT_GAME_MODE_REFRESH_RATE));
        printf("DISPLAY CHANGED = %d\n", glutGameModeGet(GLUT_GAME_MODE_DISPLAY_CHANGED));
    }

    if(key == 27)
        exit(0);
}

// captura del teclado, teclas especiales
void special_key(int key, int x, int y){
    printf("special key: # %d \n",key);
}

// llamada por GLUT automaticamente
void timer_function(int value){
    // mensaje cada 8 segundos
    printf("timer func: Posicion del puntero %d %d\n", xt, yt);
    glutTimerFunc(8000, timer_function, 1);
}

int main (int argc, char** argv){
    // funcion para iniciar la libreria glut y pasar los parametros de la consola
    glutInit (&argc, argv);

    // Usa double-buffer y modo de color RGBA
    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

    // especifica el tamaño inicial de la ventana de la aplicacion
    glutInitWindowSize (800, 600);

    // crea la ventana con el nombre simple
    glutCreateWindow ("GL Template Basic"); 

    // CALLBACK de despliegue, apuntador a funcion de renderizado
    glutDisplayFunc (display);

    // CALLBACK accion de redimensionamiento de la pantalla
    glutReshapeFunc (resize);           

    // CALLBACK captura del movimiento del raton
    glutPassiveMotionFunc(mouse_move);

    // CALLBACK captura del movimiento de arrastre del raton
    glutMotionFunc(mouse_drag);

    // CALLBACK captura del evento de presionar o liberar un boton del raton
    glutMouseFunc(mouse_click);

    // CALLBACK captura de presion de teclas anormales
    glutKeyboardFunc(normal_key);

    // CALLBACK captura de presion de teclas especiales
    glutSpecialFunc(special_key);

    // CALLBACK funcion de temporizador de opengl
    glutTimerFunc(33, timer_function, 1);

    // funcion de inicializacion
    init ( );
    //menu
    creacionMenu(); 

    // esta funcion arranca a correr la libreria glut
    glutMainLoop ( );
    return 0;
}