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
// void on_change(int, int,int, int,int, int);

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

        // trackbar func: I want to Init by origin hsv, not (0,0,0)
        // createTrackbar("H_low","HSV_window",&H_low,179, on_H_change, (void*)&channels[0]);
        // createTrackbar("H_high","HSV_window",&H_high,179, on_H_change, (void*)&channels[0]);
        // createTrackbar("S_low","HSV_window",&S_low,255, on_S_change, (void*)&channels[1]);
        // createTrackbar("S_high","HSV_window",&S_high,255, on_S_change, (void*)&channels[1]);
        // createTrackbar("V_low","HSV_window",&V_low,255, on_V_change, (void*)&channels[2]);
        // createTrackbar("V_high","HSV_window",&V_high,255, on_V_change, (void*)&channels[2]);

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


// void on_change(int H_low, int H_high,int S_low, int S_high,int V_low, int V_high){
//     Scalar lowb(H_low, S_low, V_low);
//     Scalar highb(H_high, S_high, V_high);

//     HSVthreshold(0, lowb, highb,0);
// }

// mask each H,S,V channel
// void on_H_change(int &H_low, int &H_high, void* userdata){
//     Scalar lowb(H_low, S_low, V_low);
//     Scalar highb(H_high, S_high, V_high);

//     // Mat src = *(Mat*)userdata;
//     // channels[0] = hue+src; 

//     HSVthreshold(userdata, lowb, highb,0);
//     // Mat dst = src + (hue - src);
    
//     // Mat dst = hue+src; 
    
//     // merge(channels, img_test);
//     imshow("HSV_window",masked_img);    
// }

// void on_S_change(int sat, void* userdata){
//     // Scalar lowb(H_low, S_low, V_low);
//     // Scalar highb(H_high, S_high, V_high);
    

//     // Mat src = *(Mat*)userdata;
//     // channels[1] = sat+src; 
    
//     // channels[1] += (sat-src);
    

//     // merge(channels, vid2);
//     // merge(chn_previous, vid2);
//     imshow("HSV_window",masked_img);    
// }

// void on_V_change(int val, void* userdata){

//     // Scalar lowb(H_low, S_low, V_low);
//     // Scalar highb(H_high, S_high, V_high);
//     split (channels, vid2);
//     Mat src = *(Mat*)userdata;
//     channels[2] = val+src; 
    
//     // channels[2] += (val-src);
    

//     // for(int j=0; j<vid2.rows; j++){
//     //     for (int i=0; i< vid2.cols; i++){
//     //         int v = vid2.at<Vec3b>(j,i)[2] + (val-vid2.at<Vec3b>(j,i)[2]) ;
//     //         vid2.at<Vec3b>(j,i)[2] = v > 255 ? 255 : v< 0 ? 0: v;
//     //     }
//     // }

//     // vid2.setTo(Scalar(slider_H, slider_S, val));
//     // cvtColor(vid2,vid1,COLOR_HSV2BGR);
//     // chn_previous[2] = channels[2];

//     merge(channels, vid2);
//     // merge(chn_previous, vid2);
//     imshow("HSV_window",vid2);    
// }
