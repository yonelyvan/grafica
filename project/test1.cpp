//  g++ file.cpp -o m `pkg-config --cflags --libs opencv`
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv){
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
          Canny(frame, contours, 6000, 6000, 5, true);
        imshow("MyNegativeVideo", contours);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    	//cout << "M = "<< endl << " "  << contours << endl << endl;
    	//break;
    }

    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
