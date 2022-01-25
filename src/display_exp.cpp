// 1st GOAL : import video file & mouse & track bar prototype 
// 2nd GOAL : use ROS & stream camera & mouse & track bar prototype 
// final GOAL : convergence 1st, 2nd GOAL


// version 1 : adjust H, S, V value
// Version 2 : InRange -> mask

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include <std_msgs/Float64.h>
#include <sstream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "/home/catkin_ws/devel/include/exercise_00/VidInfo.h" // Edit this line to your own dev setup 

void on_mouse_HSV(int event, int x, int y, int flags, void*);
void on_mouse_CRDN(int event, int x, int y, int flags, void*);


using namespace cv;
using namespace std;

VideoCapture cap_sample;

// Mat mask_filter(Mat img, int w, int h, int thresh);

Mat img_test;
Mat masked_img;

Point POINT1;
// vector<Mat> channels; 

int H_low(0),S_low(0),V_low(0);
int H_high(179),S_high(255),V_high(255);

static void HSVthreshold(int, int, int, int, int ,int, void*){
    inRange(img_test, Scalar(H_low,S_low, V_low), Scalar(H_high, S_high, V_high), masked_img);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "exrc_display");
	ros::NodeHandle nh1;

    cap_sample.open("/home/Videos/sample_road.avi");
    int w_ = cap_sample.get(CAP_PROP_FRAME_WIDTH);
	int h_ = cap_sample.get(CAP_PROP_FRAME_HEIGHT);
    double fps_ = cap_sample.get(CAP_PROP_FPS);
    int delay = cvRound(1000/ fps_);
    
    Mat vid1;

    while(ros::ok()){
        cap_sample >> vid1;

        if(vid1.empty()){
            cerr<< "Ew! frame is empty"<<endl;
            break;
        }

        // cout <<"FPS: "<< fps_ << endl;

        Mat img_resize;

        resize(vid1, img_resize, Size(640, 480), 0,0);
        // imshow("Origin_resized", img_resize);

        Mat HSV_img;
        cvtColor(img_resize, HSV_img ,COLOR_BGR2HSV); // Copy vid1 as vid2 & convert bgr -> hsv
        
        img_test = HSV_img;

        namedWindow("image_raw",WINDOW_AUTOSIZE); namedWindow("Masked_window",WINDOW_AUTOSIZE); namedWindow("COORDINATE_window",WINDOW_AUTOSIZE);

        // mouse func
        setMouseCallback("Masked_window", on_mouse_HSV); setMouseCallback("COORDINATE_window", on_mouse_CRDN);

        createTrackbar("H_low","Masked_window",&H_low,179);
        createTrackbar("H_high","Masked_window",&H_high,179);
        createTrackbar("S_low","Masked_window",&S_low,255);
        createTrackbar("S_high","Masked_window",&S_high,255);
        createTrackbar("V_low","Masked_window",&V_low,255);
        createTrackbar("V_high","Masked_window",&V_high,255);

        // on_change(H_low, H_high, S_low, S_high, V_low,V_high);
        HSVthreshold(H_low, H_high, S_low, S_high, V_low,V_high,0);
        
        
        imshow("image_raw", img_resize); imshow("COORDINATE_window",img_resize); imshow("Masked_window",masked_img);

        if(waitKey(10) == 'q'){
            break;
            cerr << "END" << endl;
        }
        else if(waitKey(10) == 'p'){
            cv::waitKey(-1);
            cerr << "PAUSE"<<endl;
        }
    }
    
    destroyAllWindows();
\
    return 0;
}


//NORMAL FUNCTIONING CHECKED - use hsvcolor node.
void on_mouse_HSV(int event, int x, int y, int flags, void*){
    if (event == EVENT_LBUTTONDBLCLK){
        POINT1 = Point(x,y);
        int H = img_test.at<Vec3b>(y,x)[0];
        int S = img_test.at<Vec3b>(y,x)[1];
        int V = img_test.at<Vec3b>(y,x)[2];

        cout << "[ HSV ] [H: "<<H<<"] [S: "<<S<<"] [V: "<<V<<"]"<<endl;    
    }
}

void on_mouse_CRDN(int event, int x, int y, int flags, void*){
    if (event == EVENT_LBUTTONDOWN){
        POINT1 = Point(x,y);
        cout << "[ COORDINATE ] [X: " << x<<"] [Y: "<<y <<"]"<<endl;
    }
}
