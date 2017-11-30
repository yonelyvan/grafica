--install 
http://www.codebind.com/linux-tutorials/install-opencv-3-2-ubuntu-16-04/


------|	compilar como: g++ file.cpp -o m `pkg-config --cflags --libs opencv`	|-----
#include "opencv2/opencv.hpp"
using namespace cv;
int main(int argc, char** argv)
{
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return 0;
    for(;;)
    {
          Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow("this is you, smile! :)", frame);
          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}


----------------