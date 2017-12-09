//  g++ file.cpp -o m `pkg-config --cflags --libs opencv`
#include "opencv2/opencv.hpp"
using namespace cv;





int main(int argc, char** argv){
    
	int threshold=2500;
    VideoCapture cap;//camara por defecto

    if(!cap.open(0))
        return 0;
    //cap.set(CAP_PROP_FRAME_WIDTH, 640);
	//cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	//cap.set(CV_CAP_PROP_FRAME_COUNT, 30);
	//cap.set(CAP_PROP_EXPOSURE, 1000);
	//cap.set(CAP_PROP_ISO_SPEED, 10); 
	//cap.set(CV_CAP_PROP_BRIGHTNESS, 0.0); 

    while(true){
		Mat frame;
		cap >> frame;
		if( frame.empty() ) break; // end of video stream
		imshow("this is you, smile! :)", frame);
		Mat contornos;
		Canny(frame, contornos, threshold, threshold*2, 5, true);
		imshow("contornos", contornos);

		if( waitKey(100) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}


/*
https://askubuntu.com/questions/856460/use-a-digital-camera-canon-as-webcam

sudo modprobe v4l2loopback

gphoto2 --stdout --capture-movie | ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p -threads 0 -f v4l2 /dev/video1
gphoto2 --stdout --capture-movie | ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p -threads 0 -f v4l2 /dev/video0


*/