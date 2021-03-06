//g++ practica2.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>
GLsizei winWidth = 600, winHeight = 500;    // Initial display window size.
GLint xRaster = 25, yRaster = 150;          // Initialize raster position. 

GLubyte label[36] = {	'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r', 
						'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n', 
						'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p', 
						'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c'}; 
GLint dataValue [12] = {420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438};

void init (void){
	glClearColor (1.0, 1.0, 1.0, 0.2);    // White display window.
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void lineGraph (void){
	GLint month, k;
	GLint x = 30;                        // Initialize x position for chart.

	glClear (GL_COLOR_BUFFER_BIT);       //  Clear display window.
	glColor3f (0.0, 0.0, 1.0);           //  Set line color to blue.
	glBegin (GL_LINE_STRIP);             //  Plot data as a polyline.
		for (k = 0; k < 12; k++)
			glVertex2i (x + k*50, dataValue [k]);
	glEnd ( );


	glColor3f (1.0, 0.0, 0.0);          //  Set marker color to red.
	xRaster = 25;                       //  Display chart labels.
	for (k = 0; k < 12; k++) {          //  Plot data as asterisk polymarkers. 
		glRasterPos2i (xRaster + k*50, dataValue [k] - 4);
		glutBitmapCharacter (GLUT_BITMAP_9_BY_15, '*');
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


void barChart (void){
   	GLint month, k;
   	glClear (GL_COLOR_BUFFER_BIT); 
   	glColor3f (0.0, 0.0, 0.0);     
   	for (k = 0; k < 12; k++){
	  	glRecti (20 + k*50, 165, 40 + k*50, dataValue [k]);
   	}

   	glColor3f (0.0, 0.0, 0.0);           
  	xRaster = 20;                   
  	for (month = 0; month < 12; month++) {
	  glRasterPos2i (xRaster, yRaster);
	  for (k = 3*month; k < 3*month + 3; k++)
		 glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label[k]);
	  xRaster += 50;
   	}
   	glFlush ( );
}

void fun4(void){
	GLint month, k;
	GLint x = 30;                        
	int month_init=6;
	int month_end=12;

	glClear (GL_COLOR_BUFFER_BIT);       
	glColor3f (0.0, 0.0, 1.0);           
	glBegin (GL_LINE_STRIP);             
		for (k = month_init; k < month_end; k++)
			glVertex2i (x + k*50, dataValue [k]);
	glEnd ();

	glColor3f (1.0, 0.0, 0.0);          
	xRaster = 25;                       
	for (k = month_init; k < month_end; k++) { //macadores      
		glRasterPos2i (xRaster + k*50, dataValue [k] - 4);
		glutBitmapCharacter (GLUT_BITMAP_9_BY_15, '*');
	}

	glColor3f (0.0, 0.0, 0.0);          
	xRaster = 20 + month_init*50;                       
	for (month = month_init; month < month_end; month++) {
		glRasterPos2i (xRaster, yRaster);
		for (k = 3*month; k < 3*month + 3; k++) //labels
		  glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label[k]);
		xRaster += 50;
	}
	glFlush ( );
	
   	glColor3f (0.0, 0.0, 0.0);     
   	for (k = month_init; k < month_end; k++){//baras
	  	glRecti (20 + k*50, 165, 40 + k*50, dataValue [k]);
   	}
   	glFlush ( );
   	
   	//linea de tendencia
	glColor3f(1,0,0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(25+month_init*50, dataValue[month_init-1]);
	glVertex2i(25+(month_end-1)*50, dataValue[month_end-1]);
	glEnd();
	glFlush();

}




int main (int argc, char** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Line Chart Data Plot");
	init();
	glutDisplayFunc(fun4);
	//glutDisplayFunc(barChart);
	glutMainLoop();
	return 0;
}

















































/*
void winReshapeFcn (GLint newWidth, GLint newHeight){
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
	glClear (GL_COLOR_BUFFER_BIT);   
}*/
