//g++ file.cpp -o m -lGL -lGLU -lglut
#include <GL/glut.h>  
#include <math.h>
 
void init(){
  glClearColor(0,0,0,0.0); //establece el color de fondo de la ventana
  glMatrixMode(GL_PROJECTION); //establece el modo de matriz actual.
  gluOrtho2D(0.0,600.0,0.0,600.0);//establece una región de visualización
}

void primitivas_opengl() {
   	glClear(GL_COLOR_BUFFER_BIT);   
 	glColor3f(0,0,1);
 	int x0,y0;
 	int it=120;
 	x0=0;
 	y0=100;
 	glBegin(GL_POINTS);
 		glPointSize(20);              
		glVertex2i(x0+40,y0+ 50);     		
		glVertex2i(x0+40,y0+ 60);     		
		glVertex2i(x0+50,y0+ 60);
		glVertex2i(x0+50,y0+ 50);     		
   	glEnd();

   	x0=it;
	glBegin(GL_LINES);
		glVertex2i(x0+10,y0+10);
		glVertex2i(x0+30,y0+60);
		glVertex2i(x0+20,y0+10);
		glVertex2i(x0+60,y0+85);
	glEnd();

	x0=2*it;
	glBegin(GL_LINE_STRIP);
		glVertex2i(x0+20,y0+20);
		glVertex2i(x0+40,y0+20);
		glVertex2i(x0+40,y0+80);
		glVertex2i(x0+60,y0+40);
		glVertex2i(x0+0,y0+56);
		glVertex2i(x0+16,y0+60);
		glVertex2i(x0+20,y0+40);
	glEnd();

	x0=3*it;
	glBegin(GL_LINE_LOOP);
		glVertex2i(x0+60,y0+10);
		glVertex2i(x0+80,y0+60);
		glVertex2i(x0+70,y0+10);
		glVertex2i(x0+110,y0+85);
		glVertex2i(x0+40,y0+40);
	glEnd();

	x0=4*it;
	glBegin(GL_POLYGON);
		glVertex2i(x0+20,y0+20);
		glVertex2i(x0+10,y0+40);
		glVertex2i(x0+20,y0+60);
		glVertex2i(x0+40,y0+60);
		glVertex2i(x0+50,y0+40);
		glVertex2i(x0+40,y0+20);
		glVertex2i(x0+20,y0+20);
	glEnd();

	x0=0;
 	y0=0;
 	glBegin(GL_TRIANGLE_STRIP);          
    	glVertex2i(x0+10,y0+10);
		glColor3f(1,0,0);
		glVertex2i(x0+50,y0+10);
		glColor3f(0,1,0);
		glVertex2i(x0+50,y0+80);
		glColor3f(0,0,1);
		glVertex2i(x0+10,y0+80);
   	glEnd();

   	x0=it;
 	glBegin(GL_TRIANGLES);          
    	glColor3f(0,1,0);
    	glVertex2i(x0+10,y0+10);
		glVertex2i(x0+10,y0+50);
		glVertex2i(x0+50,y0+10);

		glVertex2i(x0+11,y0+50);
		glVertex2i(x0+50,y0+20);
		glVertex2i(x0+50,y0+80);
   	glEnd();
   	
   	x0=it*2;
 	glBegin(GL_TRIANGLE_FAN);          
    	glVertex2i(x0+10,y0+10);
		glVertex2i(x0+80,y0+10);
		glColor3f(1,0,0);
		glVertex2i(x0+40,y0+20);
		glColor3f(0,1,0);
		glVertex2i(x0+80,y0+60);
		glColor3f(1,0,0);
		glVertex2i(x0+40,y0+50);
		glColor3f(0,0,1);
		glVertex2i(x0+15,y0+80);
   	glEnd();
   	
   	x0=it*3;
	glBegin(GL_QUADS);              
		glColor3f(0,1,0);
		glVertex2f(x0+10,y0+10);    
		glVertex2f(x0+10,y0+50);
		glVertex2f(x0+50,y0+50);
		glVertex2f(x0+50,y0+10);
		glColor3f(1,0,0);
		glVertex2f(x0+40,y0+60);
		glVertex2f(x0+80,y0+20);
		glVertex2f(x0+80,y0+80);
		glVertex2f(x0+50,y0+100);
   	glEnd();

   	x0=it*4;
   	glBegin(GL_QUAD_STRIP);         
		glColor3f(0,1,0);
		glVertex2f(x0+10,y0+10);    
		glVertex2f(x0+50,y0+10);
		glColor3f(0,0,1);
		glVertex2f(x0+10,y0+30);
		glVertex2f(x0+50,y0+50);
		glColor3f(1,0,0);
		glVertex2f(x0+0,y0+60);
		glVertex2f(x0+40,y0+70);
		glColor3f(0,1,0);
		glVertex2f(x0+40,y0+90);
		glVertex2f(x0+70,y0+100);

   	glEnd();
   	glFlush();  
}
 

void modos(){
	glClear(GL_COLOR_BUFFER_BIT); 
	int x0, y0; 
	glColor3f( 1.0, 0.0, 0.0 );           //red
	glPolygonMode( GL_FRONT, GL_FILL ); 
	glBegin( GL_POLYGON );                //draw solid polygon
		glVertex2i( 10, 10 );
		glVertex2i( 100, 10 );  
		glVertex2i( 150, 50 );   
		glVertex2i( 100, 100 );  
		glVertex2i( 50, 80 );
		glVertex2i( 10, 10 );     
	glEnd();
	x0 = 160;
	glColor3f( 0.0, 1.0, 0.0 );           //green
	glPolygonMode( GL_FRONT, GL_LINE );
	glBegin( GL_POLYGON );                //draw polygon
		glVertex2i( x0+10, 10 );
		glVertex2i( x0+100, 10 );
		glVertex2i( x0+150, 50 );
		glVertex2i( x0+100, 100 );
		glVertex2i( x0+50, 80 );  
		glVertex2i( x0+10, 10 );
	glEnd(); 
	x0 = 80;
	y0 = 120;
	glColor3f( 0.0, 0.0, 1.0 );           //blue
	glPolygonMode( GL_FRONT, GL_POINT );
	glBegin( GL_POLYGON );                //draw polygon points
		glVertex2i( x0+10, y0+10 );
		glVertex2i( x0+100, y0+10 );
		glVertex2i( x0+150, y0+50 ); 
		glVertex2i( x0+100, y0+100 );
		glVertex2i( x0+50, y0+80 );
		glVertex2i( x0+10, y0+10 );
	glEnd(); 
	glFlush(); 
}

void colores_interpolados(){
	glClear(GL_COLOR_BUFFER_BIT); 
	int x0, y0; 
	glColor3f( 1.0, 0.0, 0.0 );           //red
	glPolygonMode( GL_FRONT, GL_FILL ); 
	glBegin( GL_POLYGON );                //draw solid polygon
		glVertex2i( 10, 10 );
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex2i( 100, 10 );  
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex2i( 150, 50 );   
		glColor3f( 0.0, 1.0, 1.0 );
		glVertex2i( 100, 100 );  
		glColor3f( 1.0, 1.0, 0.0 );
		glVertex2i( 50, 80 );
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex2i( 10, 10 );     
	glEnd();

	x0=150;
	y0=10;
	int zoom=4;
	glPolygonMode( GL_FRONT, GL_FILL ); 
	glBegin(GL_POLYGON);
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex2i(x0+20*zoom,y0+20*zoom);
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex2i(x0+10*zoom,y0+40*zoom);
		glColor3f( 0.0, 1.0, 1.0 );
		glVertex2i(x0+20*zoom,y0+60*zoom);
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex2i(x0+40*zoom,y0+60*zoom);
		glColor3f( 1.0, 1.0, 0.0 );
		glVertex2i(x0+50*zoom,y0+40*zoom);
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex2i(x0+40*zoom,y0+20*zoom);
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex2i(x0+20*zoom,y0+20*zoom);
	glEnd();

	glFlush(); 
}

void patrones(){
	glClear(GL_COLOR_BUFFER_BIT); 
 	GLubyte fly[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
		0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
		0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
		0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
		0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
		0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
		0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
		0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
		0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
		0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
		0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

	GLubyte simple_pattern[] = {
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	glColor3f( 1.0f, 0.0f, 0.0f );       //rojo
	glRectf (25.0, 25.0, 125.0, 125.0);  

	glEnable(GL_POLYGON_STIPPLE);	
		glColor3f( 0.0f, 1.0f, 0.0f );//verde       
		glPolygonStipple (fly);
		glBegin(GL_POLYGON);
			glVertex2i(125,25);
			glVertex2i(175,125);
			glVertex2i(225,25);
		glEnd();
		
		glPolygonStipple( simple_pattern );
		glColor3f( 0.0f, 0.0f, 1.0f );       
	glDisable(GL_POLYGON_STIPPLE);
  	
  	glFlush(); 
}


GLubyte fly[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
	0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
	0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
	0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
	0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
	0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
	0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
	0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
	0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
	0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
	0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
	0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
	0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

GLubyte simple_pattern[] = {
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};




void art(){
	glClear(GL_COLOR_BUFFER_BIT); 
	int x0,y0;
	float zoom;
	x0=0;
 	y0=0;
 	zoom = 0.5;
 	//glPolygonMode( GL_FRONT, GL_LINE );//temporal
 	glBegin(GL_POLYGON);//parte superior de rubi
		glColor3f(0.95, 0.0, 0.17);
		glVertex2i(x0+285*zoom, y0+830*zoom);
		glVertex2i(x0+885*zoom, y0+830*zoom);
		glVertex2i(x0+1126*zoom, y0+663*zoom);
		glVertex2i(x0+582*zoom, y0+210*zoom);
		glVertex2i(x0+46*zoom, y0+663*zoom);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);//parte inferior de rubi     
		glColor3f(0.95, 0.0, 0.17);
    	glVertex2i(x0+582*zoom, y0+210*zoom);
		glColor3f(0.95, 0.0, 0.17);
		glVertex2i(x0+46*zoom, y0+664*zoom);
		glColor3f(0.82, 0.0, 0.16);
		glVertex2i(x0+374*zoom, y0+664*zoom);
		glColor3f(0.95, 0.0, 0.17);
		glVertex2i(x0+588*zoom, y0+664*zoom);
		glVertex2i(x0+803*zoom, y0+664*zoom);
		glColor3f(1.0, 0.26, 0.35);
		glVertex2i(x0+977*zoom, y0+664*zoom);
		glVertex2i(x0+1125*zoom, y0+664*zoom);
   	glEnd();

	glBegin(GL_QUADS);              
		glColor3f(1.0, 0.26, 0.35);
		glVertex2f(x0+207*zoom, y0+773*zoom);
		glVertex2f(x0+203*zoom, y0+664*zoom);
		glVertex2f(x0+431*zoom, y0+795*zoom);
		glVertex2f(x0+374*zoom, y0+829*zoom);

		glColor3f(1.0, 0.13, 0.25);
		glVertex2f(x0+431*zoom, y0+797*zoom);
		glVertex2f(x0+587*zoom, y0+663*zoom);
		glVertex2f(x0+736*zoom, y0+799*zoom);
		glVertex2f(x0+578*zoom, y0+828*zoom);

		glColor3f(0.82, 0.0, 0.16);
		glVertex2f(x0+735*zoom, y0+796*zoom);
		glVertex2f(x0+978*zoom, y0+664*zoom);
		glVertex2f(x0+944*zoom, y0+790*zoom);
		glVertex2f(x0+800*zoom, y0+829*zoom);
   	glEnd();

   	glBegin(GL_TRIANGLES);          
		glColor3f(0.69, 0.0, 0.15);
		glVertex2f(x0+201*zoom, y0+664*zoom);
		glVertex2f(x0+375*zoom, y0+662*zoom);
		glVertex2f(x0+528*zoom, y0+324*zoom);

		glColor3f(0.82, 0.0, 0.16);
		glVertex2f(x0+528*zoom, y0+324*zoom);
		glVertex2f(x0+375*zoom, y0+664*zoom);
		glVertex2f(x0+588*zoom, y0+664*zoom);

		glColor3f(0.69, 0.0, 0.15);
		glVertex2f(x0+588*zoom, y0+664*zoom);
		glVertex2f(x0+803*zoom, y0+664*zoom);
		glVertex2f(x0+650*zoom, y0+340*zoom);

		glColor3f(0.82, 0.0, 0.16);
		glVertex2f(x0+650*zoom, y0+340*zoom);
		glVertex2f(x0+804*zoom, y0+664*zoom);
		glVertex2f(x0+977*zoom, y0+664*zoom);

		glColor3f(1.0, 0.13, 0.25);
		glVertex2f(x0+977*zoom, y0+662*zoom);
		glVertex2f(x0+832*zoom, y0+430*zoom);
		glVertex2f(x0+1086*zoom, y0+661*zoom);

		glColor3f(0.82, 0.0, 0.16);
		glVertex2f(x0+201*zoom, y0+661*zoom);
		glVertex2f(x0+364*zoom, y0+408*zoom);
		glVertex2f(x0+89*zoom, y0+661*zoom);
		//trialgulos superiores
		glColor3f(0.87, 0.55, 0.67);
		glVertex2f(x0+47*zoom, y0+664*zoom);
		glVertex2f(x0+85*zoom, y0+664*zoom);
		glVertex2f(x0+170*zoom, y0+749*zoom);
		
		glColor3f(1.0, 0.49, 0.57);
		glVertex2f(x0+204*zoom, y0+664*zoom);
		glVertex2f(x0+430*zoom, y0+795*zoom);
		glVertex2f(x0+374*zoom, y0+664*zoom);

		glColor3f(1.0, 0.26, 0.34);
		glVertex2f(x0+374*zoom, y0+664*zoom);
		glVertex2f(x0+430*zoom, y0+795*zoom);
		glVertex2f(x0+584*zoom, y0+664*zoom);

		glColor3f(0.79, 0.0, 0.13);
		glVertex2f(x0+588*zoom, y0+664*zoom);
		glVertex2f(x0+736*zoom, y0+795*zoom);
		glVertex2f(x0+802*zoom, y0+664*zoom);

		glColor3f(0.66, 0.0, 0.13);
		glVertex2f(x0+802*zoom, y0+664*zoom);
		glVertex2f(x0+736*zoom, y0+796*zoom);
		glVertex2f(x0+976*zoom, y0+664*zoom);
		glColor3f(0.87, 0.55, 0.67);
		glVertex2f(x0+977*zoom, y0+664*zoom);
		glVertex2f(x0+945*zoom, y0+786*zoom);
		glVertex2f(x0+1122*zoom, y0+664*zoom);

   	glEnd();

	glEnable(GL_POLYGON_STIPPLE);	
		glColor3f(0.28, 0.29, 0.29);     
		glPolygonStipple (fly);
		glBegin(GL_TRIANGLES);
			for (int i = 0; i < 6; ++i){
				x0=100*i;
				glColor3f(0.76, 0.05, 0.21);
				glVertex2i(x0+0,y0+0);
				glVertex2i(x0+100,y0+0);
				glColor3f(0.28, 0.29, 0.29);
				glVertex2i(x0+50,y0+100);
			}
			x0=0;
			y0=600;
			for (int i = 0; i < 6; ++i){
				x0=100*i;
				glColor3f(0.76, 0.05, 0.21);
				glVertex2i(x0,y0);
				glVertex2i(x0+100,y0);
				glColor3f(0.28, 0.29, 0.29);
				glVertex2i(x0+50,y0-100);
			}
		glEnd();
		
		glPolygonStipple( simple_pattern );
	glDisable(GL_POLYGON_STIPPLE);
  	
  	glFlush(); 
}








int main(int argc, char** argv) {
    glutInit(&argc, argv); //se inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//establece el modo de visualización inicial
    glutInitWindowPosition(50,100);//estableze posición de la ventana inicial
    glutInitWindowSize(600,600);//estableze tamaño de la ventana inicial
    glutCreateWindow("Ejemplo OpenGL");//label de la ventana

    init();
    //glutDisplayFunc(primitivas_opengl); //visualizacion de una funion
    //glutDisplayFunc(modos); //visualizacion de una funion
    //glutDisplayFunc(colores_interpolados); //visualizacion de una funion
    //glutDisplayFunc(patrones); //visualizacion de una funion
    glutDisplayFunc(art); //visualizacion de una funion
    
    glutMainLoop(); //entra al ciclo de procesamiento de eventos GLUT
    exit(0);
}
