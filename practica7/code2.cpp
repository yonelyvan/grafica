// g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415

class wcPt2D {
	public:
		GLfloat x, y;
};

void init (){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-300.0, 300.0, -300.0, 300.0);
	glMatrixMode (GL_MODELVIEW);
}

void triangle (wcPt2D *verts){
	GLint k;
	glBegin (GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f (verts [k].x, verts [k].y);
	glEnd ( );
}

void triangle_(GLfloat points[3][3]){
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
        glVertex2f(points[0][i], points[1][i]);
    glEnd();
}

void flecha (wcPt2D *verts){
	GLint k;
	glBegin(GL_LINE_LOOP);
	for (k = 0; k < 7; k++)
		glVertex2f (verts [k].x, verts [k].y);
	glEnd ( );
}

void displayFcn (){
	//la posición inicial del triángulo.
    wcPt2D verts[3] = {{-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);   
    glViewport(0, 0, 300, 300); // Establece el visor izquierdo.
    triangle(verts);            // Muestra el triángulo.
    //Gira el triángulo y lo visualiza en la mitad derecha de la ventana de visualización.
    glColor3f(1.0, 0.0, 0.0);       
    glViewport(300, 0, 300, 300);   // Establece el visor
    glRotatef(90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle(verts);                // Muestra el triángulo rojo

    glFlush();
}


void displayFcn2(){
	glClear(GL_COLOR_BUFFER_BIT);   
/* 	
	glMatrixMode (GL_MODELVIEW);

	glViewport (300, 300, 200, 200);
	glColor3f (0.0, 0.0, 1.0);
	glRecti (50, 100, 200, 150); // Muestra un rectángulo azul.
	glColor3f (1.0, 0.0, 0.0);
	
	glViewport (280, 300, 200, 200);
	glTranslatef (-200.0, -50.0, 0.0); // Establece los parámetros de traslación.
	glRecti (50, 100, 200, 150); // Muestra un rectángulo rojo trasladado.

	glFlush ( );*/

	glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 300, 200); // Establece el visor izquierdo 1
    glColor3f(0.0, 0.0, 1.0);         // establece el color actual en azul.
    glRecti(50, 100, 200, 150);       // presenta un rectángulo azul.
    glPushMatrix();                   // hace una copia de la matriz identidad (superior).

    glViewport(300, 0, 300, 200);     // establece el visor derecho 1
    glColor3f(1.0, 0.0, 0.0); // establece el color actual en rojo.
    glTranslatef(-200.0, -50.0, 0.0); // establece los parámetros de traslación.
    glRecti(50, 100, 200, 150);       // muestra un rectángulo rojo trasladado.

    glViewport(0, 200, 300, 200);   // establece el visor izquierdo 2
    glPopMatrix();                  // recorre la matriz de traslación.
    glPushMatrix();                 // hace una copia de la matriz identidad (superior).
    glRotatef(90.0, 0.0, 0.0, 1.0); // define rotación de 90 grados sobre el eje z.
    glRecti(50, 100, 200, 150);     // muestra un rectángulo rojo girado.

    glViewport(300, 200, 300, 200); // establece el visor derecho 2
    glPopMatrix();              // recorre la matriz de rotación.
    glScalef(-0.5, 1.0, 1.0);   // establece los paramétros de reflexión y escala.
    glRecti(50, 100, 200, 150); // muestra un rectángulo rojo transformado.
    glFlush();
}

void displayFcn3(){
    glClear(GL_COLOR_BUFFER_BIT); 
    wcPt2D verts[8] = {{-100,-100}, {-100,100}, {0,100}, {0,200}, {100,0}, {0,-200}, {0,-100}};
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0, 0.0, 1.0);

    glViewport(0, 0, 300, 300); // visor inferior izquierdo
    glColor3f(0.0, 0.0, 1.0);
    flecha(verts); // muestra el triángulo.

    glColor3f(1.0, 0.0, 0.0);
    glViewport(0, 300, 300, 300);   // visor superior izquierdo
    glRotatef(90.0, 0.0, 0.0, 1.0); // gira alrededor del
    flecha(verts);                // muestra el triángulo rojo

    glViewport(300, 300, 300, 300); // visor superior derecho
    glRotatef(90.0, 0.0, 0.0, 1.0); // gira alrededor del
    flecha(verts);                // muestra el triángulo rojo

    glViewport(300, 0, 300, 300);   // visor inferior derecho
    glRotatef(90.0, 0.0, 0.0, 1.0); // gira alrededor del
    flecha(verts);                // muestra el triángulo rojo

    glFlush();
}





void rotar(GLfloat M_resul[3][3], GLfloat M_points[3][3], GLfloat angulo, GLfloat x, GLfloat y, GLfloat z){
    GLfloat sen_angulo, cos_angulo, tam_M_res, C;
    cos_angulo = cos(angulo * PI / 180.0);
    sen_angulo = sin(angulo * PI / 180.0);

    GLint matriz_ang[3][3] = {{cos_angulo, -sen_angulo, 0}, 
                               {sen_angulo, cos_angulo, 0},
                              {0, 0, 0}};
    int k, n, m;
    k = n = m = 3;
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < n; ++j)
        {
            M_resul[i][j] = 0;
            for (int z = 0; z < m; ++z)
                M_resul[i][j] += matriz_ang[i][z] * M_points[z][j]; 
        }

}


void displayFcn3B(){
    glClear(GL_COLOR_BUFFER_BIT); // Borra la ventana de visualización.
    //wcPt2D verts[3] = {{-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}};
    wcPt2D verts0[8] = {{-100,-100}, {-100,100}, {0,100}, {0,200}, {100,0}, {0,-200}, {0,-100}};
    int verts[8][3] = {{-100,-100,0}, {-100,100,0}, {0,100,0}, {0,200,0}, {100,0,0}, {0,-200,0}, {0,-100,0}};
    GLfloat ptos[3][3] = {  {-50.0, 50.0, 0},
                            {-25.0, -25.0, 50},
                            {0.0, 0.0, 0}};
    GLfloat res[8][3] = {0};
    GLfloat res2[3][3] = {0};
    GLfloat res3[3][3] = {0};
    // cout << "tam " << (sizeof (verts)) << endl;

    glMatrixMode(GL_MODELVIEW);
    // glColor3f(1.0, 0.0, 0.0);

    glViewport(0, 0, 300, 300); // visor abajo_izq
    glColor3f(1.0, 0.0, 0.0);
    flecha(verts0); // Muestra el triángulo.

    glViewport(0, 300, 300, 300);          // visor arriba_izq
    rotar(res, ptos, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle_(res);                        // Muestra el triángulo rojo
    //print_M(res);

    glViewport(300, 300, 300, 300);        // visor arriba_der
    rotar(res2, res, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle_(res2);                       // Muestra el triángulo ro
    //print_M(res2);

    glViewport(300, 0, 300, 300);           // visor abajo_der
    rotar(res3, res2, 90.0, 0.0, 0.0, 1.0); // Gira alrededor del
    triangle_(res3);                        // Muestra el triángulo rojo
    //print_M(res3);
    
    glFlush();
}

void desface(GLfloat M[3][3] , GLint x, GLint y){
    for (int i = 0; i < 3; i++){
        M[0][i] = M[0][i] + x;
        M[1][i] = M[1][i] + y ;
    }
}

void simetria(GLfloat M[3][3]){ //simetria axial
    for (int i = 0; i < 3; i++){
        M[1][i] = -M[1][i] ;
    }
}

void displayFcn4(){
    glClear(GL_COLOR_BUFFER_BIT);           
    int s = 20;
    GLfloat ptos[3][3] = {  {5.0 * s, 7.0 * s, 3.0* s},
                            {6.0 * s, 8.0 * s, 7.0* s},
                            {0.0 , 0.0 , 0.0}};
    
    GLfloat res[3][3] = {0};
    
    glColor3f(1.0, 0.0, 0.0);
    triangle_(ptos);                        // triangulo inicial
    
    desface(ptos, -2*s , -1*s);
    rotar(res, ptos, 90.0, 0.0, 0.0, 1.0);  //eliminar desface, Rota 90°
    desface(res, 2*s , 1*s);      //retorna el desface
    
    glColor3f(0.0, 0.5, 1.0);               //cambio de color
    triangle_(res);                         // dibuja el triangulo rotado
    
    glColor3f(0.2, 0.8, 0.0);               //cambio de color
    simetria(res);                      // simetria axial respecto a la horizontal
    triangle_(res);                         // dibuja el triangulo rotado
    glFlush();
}

int main (int argc, char ** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (600, 600);
	glutCreateWindow ("Split-Screen Example");
	init ( );
	//glutDisplayFunc (displayFcn);
	glutDisplayFunc (displayFcn3B);
	glutMainLoop ( );
	return 0;
}