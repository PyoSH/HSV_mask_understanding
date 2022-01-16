// sub : transform (input Mat => .mp4 file) until node shutdown. 
// Make video file in auto form ; you don't need to specify width, height, fps.

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

void msgcallBack(const exercise_00::VidInfo VidInfo);
void imageCallback(const sensor_msgs::ImageConstPtr &msg1);

using namespace cv;
using namespace std;

int a=0; // Global parameter that act as loop conut

int fourcc = VideoWriter::fourcc('D','I','V','X');
int delay;
exercise_00::VidInfo info_vid; // msg that bring cam & video form data
VideoWriter outputvideo; // Declare Videowriter function as global parameter

int main(int argc, char **argv)
{
	ros::init(argc, argv, "exrc_subscriber");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber img_sub = it.subscribe("/camera/exercise/image_raw",100,imageCallback); // imgmsg subscribe
    ros::Subscriber info_sub = nh.subscribe<exercise_00::VidInfo>("VidInfo",1,msgcallBack); // Video info topic subscribe

    delay = cvRound(1000/info_vid.fps);

    cout<<"!!strt!!!!!"<<endl;

    while(ros::ok()){
        cout <<"vid opened..." <<endl;
        ros::Rate loop_rate(50);           
        ros::spinOnce();
        loop_rate.sleep();
    }  
    
    outputvideo.release(); // stop writing video file
    cout << "END" <<endl;

    return 0; // shut down the program
}

void msgcallBack(const exercise_00::VidInfo VidInfo){
    info_vid.w= VidInfo.w; // copy msg data(width) to global parameter
    info_vid.h= VidInfo.h; // copy msg data(height) to global parameter
    info_vid.fps= VidInfo.fps; // copy msg data(fps) to global parameter
    
    // Make sure that "outputvideo.open(which means videowrite)" to be declared only when the file is first executed. 
    if (a == 0){  
        outputvideo.open("/home/Videos/sample_01.mp4", fourcc, info_vid.fps, Size(info_vid.w,info_vid.h));  
    }
    
    cout<<"[ w: "<<info_vid.w<<" h: "<<info_vid.h<<" fps: "<<info_vid.fps<<"] [fourcc: "<<fourcc<<"] [cnt: "<<a<<"]"<<endl;
    a++; 
}

void imageCallback(const sensor_msgs::ImageConstPtr &msg1){
    if(!outputvideo.isOpened()){
        cout<<"ewwww"<<endl;
    }
    
    Mat input = cv_bridge::toCvCopy(msg1,"bgr8")->image.clone(); // Make cv::Mat that save image data from pub node

    outputvideo.write(input); // Write video file using input matrix

    waitKey(1); // 
}
