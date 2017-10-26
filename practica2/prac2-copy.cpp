#include <GL/glut.h>

GLsizei winWidth = 600, winHeight = 500;    //tamaño de la ventana
GLint xRaster = 25, yRaster = 150;          //posición inicial

GLubyte label[36] = {	'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r', 
                      	'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n', 
                      	'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p', 
                      	'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c'}; 
GLint dataValue [12] = {420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438};

void init (void){
    glClearColor (1.0, 1.0, 1.0, 0.2);    //color de fondo de ventana
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void lineGraph (void){
    GLint month, k;
    GLint x = 30;                        //posicion inicial en x

    glClear (GL_COLOR_BUFFER_BIT);       //limpiar ventana
    glColor3f (0.0, 0.0, 1.0);           //color de linea
    glBegin (GL_LINE_STRIP);             //para dibujar lineas
        for (k = 0; k < 12; k++)
            glVertex2i (x + k*50, dataValue [k]);
    glEnd ( );


    glColor3f (1.0, 0.0, 0.0);          //color de marcador
    xRaster = 25;                       
    for (k = 0; k < 12; k++) {          
        glRasterPos2i (xRaster + k*50, dataValue [k] - 4);
        glutBitmapCharacter (GLUT_BITMAP_9_BY_15, '*');//marcar con '*'
    }


    glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
    xRaster = 20;                       //  Display chart labels.
    for (month = 0; month < 12; month++) {
        glRasterPos2i (xRaster, yRaster);
        for (k = 3*month; k < 3*month + 3; k++) 
          glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label[k]);
        xRaster += 50;
    }
    glFlush ( );
}


int main (int argc, char** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Line Chart Data Plot");
    init();
    glutDisplayFunc(lineGraph);
    glutMainLoop();
}
