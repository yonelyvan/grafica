// g++ lab4.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <stdio.h>
int windowWidth;
int windowHeight;
int init (void)
{
    glClearColor (0.4, 0.8, 0.5, 0.5);      // Establece el color de la ventana de
    glMatrixMode (GL_PROJECTION);           // visualización en blanco.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);    // Establece los parámetros de proyección.
}
void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);          //limpia la pantalla
    glColor3f (0.0, 0.4, 0.2);              //config color de linea
    glBegin (GL_LINES);
    glVertex2i (180, 15);                   //Especifica la geometría del segmento de línea.
    glVertex2i (10, 145);                   //Especifica la geometría del segmento de línea.
    // ==================
    glColor3f (0.0, 0.0, 1.0);              //config color de linea
    glLineWidth(5.0f);                      //GROSOR DE LA LINEA
    glBegin (GL_LINES);
    glVertex2i (10, 10);                   //Especifica la geometría del segmento de línea.
    glVertex2i (180, 145);

    glEnd ( );

    glFlush ( );                            // Procesa todas las subrutinas de OpenGL tan rápidamente
    
}

void resize(GLsizei w, GLsizei h)
{
    //actualiza los valores globales de tamano de ventana
    windowWidth = w;
    windowHeight = h;

    //pantalla completa
    glViewport(0, 0,w, h);

    //iniciar matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //configurar la proyeccion ortogonal
    glOrtho(0, w, 0, h, 1.f, -1.f);

    printf("resize: nuevo tamano de ventana: %dx%d\n",w,h);

    //Activa matriz del modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Inicializa GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Establece el modo de visualización.  
    glutInitWindowPosition (50, 100);               // Establece la posición de la esquina
    glutInitWindowSize (400, 300);                  // Establece el ancho y la altura de la ventana de visualización.
    glutCreateWindow ("An Example OpenGL Program"); // Crea la ventana de visualización.

    init ( );                           // Ejecuta el procedimiento de inicialización.
    glutDisplayFunc (lineSegment);      // Envía los gráficos a la ventana de visualización.
    glutReshapeFunc (resize);			// Especifica las acciones que hay que tomar cuando se modifican

    glutMainLoop ( );                   // Muestra todo y espera.
}