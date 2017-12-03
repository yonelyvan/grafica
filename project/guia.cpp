#include "recognition.h"

using namespace std;
using namespace cv;

recognition::recognition()
{
    iLowH  = 0, iLowS =0, iLowV = 200   ;  //vaso 200 plato 118 cono 218
    iHighH = 500;
    iHighS = iHighV = 500;
    theta = 25*((22/7)/180.0); //30 grados
    rotation = 0.0;
}


void recognition::init(){
    trackBar();
    recog();
}

void setPixel (int x, int y){
    glBegin (GL_POINTS);
    glVertex2i (x,y);
    glEnd();
}

void recognition::trackBar(){
    namedWindow("Control", CV_WINDOW_AUTOSIZE);
    cvCreateTrackbar("LowH","Control", &iLowH, 500);
    cvCreateTrackbar("HighH","Control", &iHighH,500);

    cvCreateTrackbar("LowS","Control", &iLowS, 500);
    cvCreateTrackbar("HighS","Control", &iHighS,500);

    cvCreateTrackbar("LowV","Control", &iLowV, 500);
    cvCreateTrackbar("HighV","Control", &iHighV,500);
}


void calibration(Mat &imgOriginal){
    CvPoint mid_bottom, mid_top;
            mid_bottom.x = 640/2;
            mid_bottom.y = 0;
            mid_top.x = 640/2;
            mid_top.y = 480;
            IplImage frame_ipl = imgOriginal;

     cvLine(&frame_ipl, mid_bottom, mid_top, CV_RGB(0,255,0), 2);
}


void recognition::recog(){

    VideoCapture cap(1);
    if( !cap.isOpened()){
        cout<<"no se pudo abrir a camara"<<endl;
        return;
    }
    int cont = 0;
    int x,y;
    while(true){
        Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal);

        if(!bSuccess){
            cout<<"No puede leer frame de el video stream"<<endl;
            continue;
        }
        //cout<<cap.get(CV_CAP_PROP_FRAME_WIDTH)<<"  "<<cap.get(CV_CAP_PROP_FRAME_HEIGHT)<<endl;
        //resize(imgOriginal, imgOriginal,Size(900,900),0,0,INTER_CUBIC);
        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
        Mat imgThresholded;
        calibration(imgOriginal);
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),Scalar(iHighH,iHighS,iHighV), imgThresholded);

        erode(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(5,1)));
        erode(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(10,5)));
        dilate(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(1,20)));
        dilate(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(1,10)));

        Mat salida =imgThresholded.clone();
        Canny(imgThresholded, salida, 100, 200);
        vector< vector< Point> > contours;
        map<int,int> mPoints;

        imshow("thresholder image", imgThresholded);
        findContours(salida, contours, RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
        imshow("thresholder image", imgThresholded);

        drawContours(imgOriginal, contours, -1, Scalar(0,255,0),CV_FILLED);
        getMediaPoints(contours,mPoints);

        vector<Point> mp;
        int _X,_Z;

        cout<<cont<<"casascacas "<< rotation<<endl;

        if(cont > 15 && cont < 355)
        {
            for(const auto &myPair : mPoints){
                imgOriginal.at<Vec3b>(Point(myPair.second, myPair.first) ) = cv::Vec3b(255, 0, 0);
                mp.push_back(Point(myPair.second,myPair.first));
                triangulation(myPair.second,myPair.first,_X,_Z);
                vector<int> tmp;
                tmp.push_back(_X);
                tmp.push_back(myPair.first + 50);
                tmp.push_back(_Z);
                pointCloud.push_back(tmp);
            }
            rotation+= 1*((  22/7)/180.0);
            saveObj();
        }else{
            break;
        }

    /*
        IplImage frame_ipl = imgOriginal;
        for(int i=0;i<mp.size();++i){
            if(i+1 ==   mp.size()){
                continue;
            }
            cvLine(&frame_ipl,mp[i],mp[i+1],CV_RGB(0,255,0), 2);
        }
*/
        imshow("canny",salida);
        imshow("original", imgOriginal);
        //imshow("thresholder image", imgThresholded);

        if(waitKey(30) == 27){
            cout<<"esc key is pressed by user"<<endl;
            break;
        }

        //imwrite(to_string(cont) + ".png", imgOriginal);
        cont++;
    }

}

/*
void recognition::triangulation(int x, int y, int &_X, int &_Z){
    //int r = x/(sin(theta));
    //int z = sqrt(pow(r,2) - pow(x,2));
    int radio = x/sin(theta);
    //_X = x*cos(rotation) - z*sin(rotation);
    //_Z = x*sin(rotation) + z*cos(rotation);
    _X = radio*cos(rotation);
    _Z = radio*sin(rotation);
}
*/

void recognition::triangulation(int x, int y, int &_X, int &_Z){
    x = (240-x)*1.5;
    _X = x*cos(rotation);
    _Z = -x*sin(rotation);
}


void recognition::getMediaPoints(vector<vector<Point> > contours, map<int,int> &mPoints){
    if(contours.size()){
        map<int,int>::iterator it;

        //#pragma omp parallel for
        for(int i=0; i<contours.size(); ++i){
            for(int j =0; j < contours[i].size(); ++j){
                it = mPoints.find( contours[i][j].y );
                if( it != mPoints.end() ){
                    mPoints[contours[i][j].y ] = ( mPoints[ contours[i][j].y ] + contours[i][j].x )/2;
                }else{
                    mPoints[ contours[i][j].y ] = contours[i][j].x;
                }
            }
        }
    }
}



void recognition::saveObj(){
    ofstream myfile("objeto.obj");
    string ver = "v ";

    for(int i=0;i<pointCloud.size();++i){
       myfile << "v "<<pointCloud[i][0]<<" "<<pointCloud[i][1]<<" "<<pointCloud[i][2]<<endl;
    }
    myfile.close();

}