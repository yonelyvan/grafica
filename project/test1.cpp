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

//solo muestra los contornos
/*
void contornos(){
	VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return 0;
    while(1){
          Mat frame;
          Mat contours;
          cap >> frame;
          flip(frame, frame, 1);
          if( frame.empty() ) break; // end of video stream
          imshow("captura", frame);
          Canny(frame, contours, 5000, 5000, 5, true);
        imshow("MyNegativeVideo", contours);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    	//cout << "M = "<< endl << " "  << contours << endl << endl;
    	//break;
    }
    // the camera will be closed automatically upon exit
    //cap.close();
}

*/





void test(){
    Mat frame = imread("img.jpg");
    Mat contours;
    imshow("img", frame);
    Canny(frame, contours, 5000, 5000, 5, true);
    imshow("MyNegativeVideo", contours);
    show(contours.rows)
    show(contours.cols)


    Vec3b color;
    int blue, green, red, promedio;

    for (int i = 0; i < contours.rows; ++i){
    	for (int j = 0; j < contours.cols; ++j){
    		color = contours.at<Vec3b>(Point(i, j));
    		blue = color.val[0];
        	green = color.val[1];
       	 	red = color.val[2];
       	 	promedio = (red+green+blue)/3; 
       	 	if( promedio >= 250  ){
       	 		//cout << i<<" "<<j<<":" << blue <<" "<<green<<" "<< red<<endl;
       	 		VP.push_back( point(j,i) );//y:filas x:columans
       	 	}
    	}
    }


    if( waitKey(1e6) == 27) {//break; // stop capturing by pressing ESC
		//cout << "M = "<< endl << " "  << contours << endl << endl;
		cout<<"OK"<<endl;
    }
}

// escribir puntos blancos en fichero
void print_poits(){
	int num_points=VP.size();
	show(num_points);
	ofstream myfile;
	myfile.open("points/points.txt");
	for (int i = 0; i < VP.size(); ++i){
		//cout<<VP[i].X<<" "<<VP[i].Y<<endl;
		float r = 102.0 ;
		float an = ((VP[i].X*360)/480)*PI/180;
		//myfile <<r*cos(an) <<" "<<VP[i].Y<<" "<< r*sin(an) <<'\n';
		myfile <<VP[i].X <<" "<<VP[i].Y<<" "<< 0 <<'\n';
	}
	myfile.close();
}



int main(int argc, char** argv){

    test();
    print_poits();
	return 0;
}







