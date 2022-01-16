// 1st GOAL : import video file & mouse & track bar prototype 
// 2nd GOAL : use ROS & stream camera & mouse & track bar prototype 
// final GOAL : convergence 1st, 2nd GOAL

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
// void imageCallback(const sensor_msgs::ImageConstPtr &msg1);
// void on_mouse(int event, int x, int y, int flags, void*);
void on_H_change(int pos, void* userdata);
void on_S_change(int pos, void* userdata);
void on_V_change(int pos, void* userdata);

using namespace cv;
using namespace std;

VideoCapture cap_sample;

Mat3b vid1, vid2, vid3;
// Mat vid1, vid2, vid3;
// Point POINT1;
int H_low(0),H_high(179),S_low(0),S_high(255),V_low(0),V_high(255);

// Scalar hsv_1;

int main(int argc, char **argv)
{
    // ros::init(argc, argv, "exrc_subscriber");
	// ros::NodeHandle nh1;

    // image_transport::ImageTransport it(nh1);
    // image_transport::Subscriber img_raw_sub = it.subscribe("/camera/exercise/image_raw",100,imageCallback);

    cap_sample.open("/home/Videos/sample4.mp4");
    // int w_ = cap_sample.get(CAP_PROP_FRAME_WIDTH);
	// int h_ = cap_sample.get(CAP_PROP_FRAME_HEIGHT);
    // double fps_ = cap_sample.get(CAP_PROP_FPS);
    // int delay = cvRound(1000/ fps_);

    

    while(true){
        

        
        cap_sample >> vid1;
        // vid1.resize(320,240);
        // vid2 = vid1.clone(); // clone
        vid3 = vid1.clone(); // clone 
        // waitKey(1);
        cvtColor(vid1, vid2,COLOR_BGR2HSV); // Copy vid1 as vid2 & convert bgr -> hsv
    
        if(vid1.empty()){
            cerr << "Ew! file is empty " <<endl;
            return -1;
        }

        // pop-up window
        namedWindow("image_raw"); namedWindow("HSV_window"); //namedWindow("COORDINATE_window");
        
        // mouse func
        // setMouseCallback("HSV_window", on_mouse); setMouseCallback("COORDINATE_window", on_mouse);
        
        

        on_H_change(0, 0);
        on_S_change(0, 0);
        on_V_change(0, 0);
        imshow("image_raw", vid1); imshow("HSV_window",vid2);// imshow("COORDINATE_window",vid3);  



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

// void imageCallback(const sensor_msgs::ImageConstPtr &msg1){
//     vid1 = cv_bridge::toCvShare(msg1,"bgr8")->image.clone();


// }



void on_H_change(int hue, void* userdata){
    // Scalar lowb(H_low, S_low, V_low);
    // Scalar highb(H_high, S_high, V_high);
    vid2.setTo(Scalar(hue, S_low, V_low));
    // vid2.convertTo(vid2, -1, )

    imshow("HSV_window",vid2);
}

void on_S_change(int sat, void* userdata){
    // Scalar lowb(H_low, S_low, V_low);
    // Scalar highb(H_high, S_high, V_high);
    
    vid2.setTo(Scalar(H_low, sat, V_low));
    

    imshow("HSV_window",vid2);
}

void on_V_change(int val, void* userdata){
    // Scalar lowb(H_low, S_low, V_low);
    // Scalar highb(H_high, S_high, V_high);
    
    vid2.setTo(Scalar(H_low, S_low, val));
    // cvtColor(vid2,vid1,COLOR_HSV2BGR);

    imshow("HSV_window",vid2);
}
