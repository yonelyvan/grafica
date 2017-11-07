/*****************************************************
Programa que activa los eventos de interfaz del usuario
manejo de raton, teclado y timer. Uso del color,
al hacer click se obtiene el color se un pixel.
******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
// g++ lab4_2.cpp -o m -lGL -lGLU -lglut

// ******* Seccion de variables globales ****************
// dimensiones de la pantalla
int windowWidth;
int windowHeight;

// variables de control del puntero
int xi, xf, xt;
int yi, yf, yt;
// ******************************************************

// Configuracion inicial del programa
int init (void)
{
    // color usado al limpiar la ventana
    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
}

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
void resize(GLsizei w, GLsizei h)
{
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
void mouse_move(int x, int y)
{
    // captura la posicion del puntero todo el tiempo
    xt = x;
    yt = windowHeight - y;
    glutPostRedisplay();
}

// captura el movimiento pasivo del raton
void mouse_drag(int x, int y)
{
    xf = x;
    yf = windowHeight - y;
    // manda a ppintar (metodo display)
    glutPostRedisplay();
}

typedef GLubyte Color[3];

void getPixel(int x, int y, Color rgb)
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb);
}

// captura el evento de clic
void mouse_click(int button, int state, int x, int y)
{
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
void normal_key(GLubyte key,int x, int y)
{
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
void special_key(int key, int x, int y)
{
    printf("special key: # %d \n",key);
}

// llamada por GLUT automaticamente
void timer_function(int value)
{
    // mensaje cada 8 segundos
    printf("timer func: Posicion del puntero %d %d\n", xt, yt);
    glutTimerFunc(8000, timer_function, 1);
}

int main (int argc, char** argv)
{
    // funcion para iniciar la libreria glut y pasar los parametros de la consola
    glutInit (&argc, argv);

    // Usa double-buffer y modo de color RGBA
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    
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

    // esta funcion arranca a correr la libreria glut
    glutMainLoop ( );

    return 0;
}