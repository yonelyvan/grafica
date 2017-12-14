// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265
using namespace std;

class wcPt2D{
  public:
    GLfloat x, y, z;
};

void init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-600.0, 600.0, -600.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
}

void triangle(wcPt2D *verts){
    GLint k;
    glBegin(GL_TRIANGLES);
    for (k = 0; k < 3; k++)
        glVertex2f(verts[k].x, verts[k].y);
    glEnd();
}

void triangle2(GLfloat pts[3][3]){
    GLint k, m;
    glBegin(GL_TRIANGLES);
    for (k = 0; k < 3; k++)
        // for (m = 0; m < 3; m++)
        glVertex2f(pts[0][k], pts[1][k]);
    glEnd();
}

void displayFcn(void){
    /* Define la posición inicial del triángulo. */
    wcPt2D verts[3] = {{-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}};

    glClear(GL_COLOR_BUFFER_BIT); // Borra la ventana de visualización.
    glColor3f(0.0, 0.0, 1.0);   // Establece el color de relleno en azul.
    glViewport(0, 0, 300, 300); // Establece el visor izquierdo.
    triangle(verts);            // Muestra el triángulo.
    /* Gira el triángulo y lo visualiza en la mitad derecha de la ventana de visualización. */
    glColor3f(1.0, 0.0, 0.0);       // Establece el color
    glViewport(300, 0, 300, 300);   // Establece el visor
    glRotatef(90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle(verts);                // Muestra el triángulo rojo

    glFlush();
}

void displayFcn2(){

    glClear(GL_COLOR_BUFFER_BIT); // Borra la ventana de visualización.
/*
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 300, 200); // Establece el visor izquierdo 1
        glColor3f(0.0, 0.0, 1.0);
        glRecti(50, 100, 200, 150); // Muestra un rectángulo azul.

    glViewport(300, 0, 300, 200);     // Establece el visor derecho 1
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-200.0, -50.0, 0.0); // Establece los parámetros de traslación.
        glRecti(50, 100, 200, 150);       // Muestra un rectángulo rojo trasladado.

    glViewport(0, 200, 300, 200);   // Establece el visor izquierdo 2
        glLoadIdentity();               // Carga la matriz identidad como matriz actual.
        glRotatef(90.0, 0.0, 0.0, 1.0); // Establece una rotación de 90 grados alrededor del eje z .
        glRecti(50, 100, 200, 150);     // Muestra un rectángulo rojo girado.

    glViewport(300, 200, 300, 200); // Establece el visor derecho 2
        glLoadIdentity();               // Carga la matriz identidad como matriz actual.
        glScalef(-0.5, 1.0, 1.0);       // Establece los parámetros de reflexión y escala.
        glRecti(50, 100, 200, 150);     // Muestra un rectángulo rojo transformado.
*/
    /////////////////////////////////////////////
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 300, 200); // Establece el visor izquierdo 1
    glColor3f(0.0, 0.0, 1.0);         // Establece el color actual en azul.
    glRecti(50, 100, 200, 150);       // Presenta un rectángulo azul.
    glPushMatrix();                   // Hace una copia de la matriz identidad (superior).

    glViewport(300, 0, 300, 200);     // Establece el visor derecho 1
    glColor3f(1.0, 0.0, 0.0); // Establece el color actual en rojo.
    glTranslatef(-200.0, -50.0, 0.0); // Establece los parámetros de traslación.
    glRecti(50, 100, 200, 150);       // Muestra un rectángulo rojo trasladado.

    glViewport(0, 200, 300, 200);   // Establece el visor izquierdo 2
    glPopMatrix();                  // Recorre la matriz de traslación.
    glPushMatrix();                 // Hace una copia de la matriz identidad (superior).
    glRotatef(90.0, 0.0, 0.0, 1.0); // Define rotación de 90 grados sobre el eje z.
    glRecti(50, 100, 200, 150);     // Muestra un rectángulo rojo girado.

    glViewport(300, 200, 300, 200); // Establece el visor derecho 2
    glPopMatrix();              // Recorre la matriz de rotación.
    glScalef(-0.5, 1.0, 1.0);   // Establece los paramétros de reflexión y escala.
    glRecti(50, 100, 200, 150); // Muestra un rectángulo rojo transformado.
    glFlush();
}

void displayFcn3(){
    glClear(GL_COLOR_BUFFER_BIT); // Borra la ventana de visualización.
    wcPt2D verts[3] = {{-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}};
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0, 0.0, 1.0);

    glViewport(0, 0, 300, 300); // visor abajo_izq
    glColor3f(0.0, 0.0, 1.0);
    triangle(verts); // Muestra el triángulo.

    glViewport(0, 300, 300, 300);   // visor arriba_izq
    glRotatef(90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle(verts);                // Muestra el triángulo rojo

    glViewport(300, 300, 300, 300); // visor arriba_der
    glRotatef(90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle(verts);                // Muestra el triángulo rojo

    glViewport(300, 0, 300, 300);   // visor abajo_der
    glRotatef(90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle(verts);                // Muestra el triángulo rojo

    glFlush();
}

void print_M(GLfloat pts[3][3]){
    int k, m;
    for (k = 0; k < 3; k++)
    {
        cout << endl;
        for (m = 0; m < 3; m++)
        {
            cout << pts[k][m] << " ";
        }
    }
    cout << "\n------------ fin ----------------" << endl;
}

void rotar(GLfloat M_resul[3][3], GLfloat M_ptos[3][3], GLfloat angulo, GLfloat x, GLfloat y, GLfloat z){

    GLfloat sen_angulo, cos_angulo, tam_M_res, C;

    sen_angulo = sin(angulo * PI / 180.0);
    cos_angulo = cos(angulo * PI / 180.0);

    GLint matriz_ang[3][3] = {{cos_angulo, -sen_angulo, 0},
                              {sen_angulo, cos_angulo, 0},
                              {0, 0, 0}};
    // print_M(matriz_ang);

    //k=filas , m=columnas || m filas , n = columnas
    int k, n, m;
    k = n = m = 3;
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < n; ++j)
        {
            M_resul[i][j] = 0;
            for (int z = 0; z < m; ++z)
                M_resul[i][j] += matriz_ang[i][z] * M_ptos[z][j]; // M_ptos[z][j];
        }
    
    // print_M(M_resul);
}

void displayFcn3B(){
    glClear(GL_COLOR_BUFFER_BIT); // Borra la ventana de visualización.
    wcPt2D verts[3] = {{-50.0, -25.0, 0}, {50.0, -25.0, 0}, {0.0, 50.0, 0}};
    GLfloat ptos[3][3] = {  {-50.0, 50.0, 0},
                            {-25.0, -25.0, 50},
                            {0.0, 0.0, 0}};
    GLfloat res[3][3] = {0};
    GLfloat res2[3][3] = {0};
    GLfloat res3[3][3] = {0};
    // cout << "tam " << (sizeof (verts)) << endl;

    glMatrixMode(GL_MODELVIEW);
    // glColor3f(1.0, 0.0, 0.0);

    glViewport(0, 0, 300, 300); // visor abajo_izq
    glColor3f(1.0, 0.0, 0.0);
    triangle(verts); // Muestra el triángulo.

    glViewport(0, 300, 300, 300);          // visor arriba_izq
    rotar(res, ptos, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle2(res);                        // Muestra el triángulo rojo
    print_M(res);

    glViewport(300, 300, 300, 300);        // visor arriba_der
    rotar(res2, res, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle2(res2);                       // Muestra el triángulo ro
    print_M(res2);

    glViewport(300, 0, 300, 300);           // visor abajo_der
    rotar(res3, res2, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle2(res3);                        // Muestra el triángulo rojo
    print_M(res3);
    
    glFlush();
}

void desface(GLfloat Mtx[3][3] , GLint x, GLint y){

    GLint k, m;
    
    for (k = 0; k < 3; k++){
        Mtx[0][k] = Mtx[0][k] + x;
        Mtx[1][k] = Mtx[1][k] + y ;
    }
}

void simetria_axl(GLfloat Mtx[3][3]){

    GLint k, m;
    
    for (k = 0; k < 3; k++){
        // Mtx[0][k] = Mtx[0][k] + x;
        Mtx[1][k] = -Mtx[1][k] ;
    }
}

void displayFcn4(){
    glClear(GL_COLOR_BUFFER_BIT);           // Borra la ventana de visualización.
    GLint escala = 60;
    GLfloat ptos[3][3] = {  {5.0 * escala, 7.0 * escala, 3.0* escala},
                            {6.0 * escala, 8.0 * escala, 7.0* escala},
                            {0.0 , 0.0 , 0.0}};
    
    GLfloat res[3][3] = {0};
    
    glColor3f(1.0, 0.0, 0.0);
    triangle2(ptos);                        // Dibuja el triangulo inicial
    
    desface(ptos, -2*escala , -1*escala);
    rotar(res, ptos, 90.0, 0.0, 0.0, 1.0);  // Antes, eliminar desface, Rota 90°
    desface(res, 2*escala , 1*escala);      // Devuelve el desface
    
    glColor3f(0.0, 0.5, 1.0);               //Cambio de color
    triangle2(res);                         // Dibuja el triangulo rotado
    
    glColor3f(0.2, 0.8, 0.0);               //Cambio de color
    simetria_axl(res);                      // Simetria axial respecto a la horizontal
    triangle2(res);                         // Dibuja el triangulo rotado
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotar ");

    init();
    //glutDisplayFunc(displayFcn4);
    glutDisplayFunc(displayFcn4);
    glutMainLoop();
    return 0;
}