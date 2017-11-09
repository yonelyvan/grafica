// g++ file.cpp -o m -lGL -lGLU -lglut
/******************************************************************** 
Programa que genera un menu de opciones
 en el cual se ejecuta con un clic derecho y genera la estructura:
 Menu principal con: color de fondo y color de dibujo
 Sub-menu color de fondo tenemos: negro, verde osucro y azul oscuro
 Sub-menu color de dibujo tenemos: balcno, verde claro y azul claro
********************************************************************/
#include <GL/glut.h>
int iFondo = 0;
int iDibujo = 3;

// coleccion de constantes para determinar los colores a usar
typedef enum {FONDO1,FONDO2,FONDO3,FONDO4,DIBUJO1,DIBUJO2,DIBUJO3,DIBUJO4}
opcionesmenu;

void onMenu(int opcion){
    // dependiendo del menu seleccionadop se configuran las
    // variables iFondo e iDibujo con un color pre-determinado
    switch(opcion){
        case FONDO1: iFondo = 0; break;
        case FONDO2: iFondo = 1; break;
        case FONDO3: iFondo = 2; break;
        case DIBUJO1: iDibujo = 3; break;
        case DIBUJO2: iDibujo = 4; break;
        case DIBUJO3: iDibujo = 5; break;
    }
    glutPostRedisplay();
}

void creacionMenu(void){
    int menuFondo, menuDibujo, menuPrincipal;

    // glutAddMenuEntry genera una opcion para seleccionar
    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Negro", FONDO1);
    glutAddMenuEntry("Verde oscuro", FONDO2);
    glutAddMenuEntry("Azul oscuro", FONDO3);

    menuDibujo = glutCreateMenu(onMenu);
    glutAddMenuEntry("blanco", DIBUJO1);
    glutAddMenuEntry("Verde claro", DIBUJO2);
    glutAddMenuEntry("Azul claro", DIBUJO3);

    // glutAddSubMenu genera una entrada de menu a la que se le
    // asocian los respectivos submenus
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Color de fondo", menuFondo);
    glutAddSubMenu("Color de dibujo", menuDibujo);

    // se dispone al clic derecho para ejecutar el menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display(void){
    float colores[6][3] = {
        {0.00f, 0.00f, 0.00f}, // 0 - negro
        {0.06f, 0.25f, 0.13f}, // 1 - verde osucro
        {0.10f, 0.07f, 0.33f}, // 2 - azul osucro
        {1.00f, 1.00f, 1.00f}, // 3 - blanco
        {0.12f, 0.50f, 0.26f}, // 4 - verde claro
        {0.20f, 0.14f, 0.66f}, // 5 - azul claro
    };

    // configura el color de fondo seleccionado
    glClearColor(colores[iFondo][0], colores[iFondo][1], colores[iFondo][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // configura el color del grafico seleccionado
    glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);

    // pinta una tetera con una primitiva 3D de glut
    glutWireTeapot(0.5);

    glFlush();
    glutSwapBuffers();
}

int main (int argc, char** argv){
    glutInit (&argc, argv);                         // Inicializa GLUT.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // Establece el modo de visualización.  
    glutInitWindowSize (400, 400);                  // Establece el ancho y la altura de la ventana de visualización.
    glutInitWindowPosition (100, 100);               // Establece la posición de la esquina
    glutCreateWindow ("Ejemplo de menus"); // Crea la ventana de visualización.
    // init ( );                           // Ejecuta el procedimiento de inicialización.
    glutDisplayFunc (display);          // Envía los gráficos a la ventana de visualización.
    creacionMenu();    
    glutMainLoop();                   // Muestra todo y espera.
    return 0;
}