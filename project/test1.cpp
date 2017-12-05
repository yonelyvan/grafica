//  g++ file.cpp -o m `pkg-config --cflags --libs opencv`
#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h> 
#define X first
#define Y second
#define show(X) cout<<#X<<" : "<<X<<endl;
#define PI 3.14159265
using namespace cv;
using namespace std;


typedef pair<int,int> point;
typedef vector< point > v_points;

v_points VP;

void test(){
	int threshold=2500;
    Mat img = imread("img.jpg");
    imshow("img", img);//imagen original
    //para mejoras aplicar filtros como como blur gaus ... para eliminar ruido
    //1)imagen a griz
	Mat img_gray;
    cvtColor( img, img_gray, CV_BGR2GRAY );
    imshow("gris", img_gray);
    //2) extraer contornos
    Mat contornos;
    Canny(img_gray, contornos, threshold, threshold*2, 5, true);
    imshow("contornos", contornos);
    //2) obtener puntos de los contornos
    vector<vector<Point> > p_contornos;
    //findContours( contours, found_contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    findContours(contornos, p_contornos, RETR_LIST,CV_CHAIN_APPROX_NONE); //CV_CHAIN_APPROX_SIMPLE);
    
    //guardar puntos en un vector de puntos (VP)
    for (int i = 0; i < p_contornos.size(); ++i){
    	for (int j = 0; j < p_contornos[i].size(); ++j){
    		int xx= p_contornos[i][j].x;
    		int yy= p_contornos[i][j].y;
    		VP.push_back( point(xx,yy) );//y:filas x:columnas
    	}
    }
    if( waitKey(1e6) == 27){ cout<<"OK"<<endl; }
}

// escribir puntos blancos en fichero
void print_poits(){
	int num_points=VP.size();
	show(num_points);
	ofstream myfile;
	myfile.open("points/points.txt");
	for (int i = 0; i < VP.size(); ++i){
		myfile <<VP[i].X <<" "<<480-VP[i].Y<<" "<< 0 <<'\n';
	}
	myfile.close();
}



int main(int argc, char** argv){
    test();
    print_poits();
	return 0;
}

//cout<<VP[i].X<<" "<<VP[i].Y<<endl;
//float r = 102.0 ;
//float an = ((VP[i].X*360)/480)*PI/180;
//myfile <<r*cos(an) <<" "<<VP[i].Y<<" "<< r*sin(an) <<'\n';