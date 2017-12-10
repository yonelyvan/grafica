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

void test(string file_name){
	int threshold=240;
    Mat img = imread(file_name);
    //imshow("img", img);//imagen original
    //para mejoras aplicar filtros como blur gaus ... para eliminar ruido
    //1)imagen a griz
	Mat img_gray;
    cvtColor( img, img_gray, CV_BGR2GRAY );
    //imshow("gris", img_gray);
    //2) extraer contornos
    Mat contornos;
    Canny(img_gray, contornos, threshold, threshold*2, 5, true);
    //imshow("contornos", contornos);
    
    //3) obtener puntos de los contornos
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
    if( waitKey(1e2) == 27){ cout<<"OK"<<endl; }
}

// escribir puntos blancos en fichero
void print_poits(string name_only){
	int num_points=VP.size();
	show(num_points);
	ofstream myfile;
	myfile.open("points/"+name_only+".txt");
	for (int i = 0; i < VP.size(); ++i){
		myfile <<VP[i].X <<" "<<480-VP[i].Y<<" "<< 0 <<'\n';
	}
	myfile.close();
}



int main(int argc, char** argv){
    string n_file;
    n_file = argv[1];//campana-0.jpg
    int l = n_file.size();
    string name_only = n_file.substr(0,l-4);
    show(n_file);
    test(n_file);
    print_poits(name_only);
	return 0;
}

//cout<<VP[i].X<<" "<<VP[i].Y<<endl;
//float r = 102.0 ;
//float an = ((VP[i].X*360)/480)*PI/180;
//myfile <<r*cos(an) <<" "<<VP[i].Y<<" "<< r*sin(an) <<'\n';


/*
https://askubuntu.com/questions/856460/use-a-digital-camera-canon-as-webcam
gphoto2 --stdout --capture-movie | ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p -threads 0 -f v4l2 /dev/video1

*/



