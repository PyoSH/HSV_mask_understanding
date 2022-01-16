
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
using namespace cv;
using namespace std;

exercise_00::VidInfo VidInfoWrite(VideoCapture camera,exercise_00::VidInfo info){
	info.w = camera.get(CAP_PROP_FRAME_WIDTH);
	info.h = camera.get(CAP_PROP_FRAME_HEIGHT);
	info.fps = camera.get(CAP_PROP_FPS);
	return info;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "exrc_publisher");
	ros::NodeHandle nh1;

	image_transport::ImageTransport it(nh1);
	image_transport::Publisher image_raw_pub = it.advertise("/camera/exercise/image_raw",100);

	ros::Publisher VidInfo = nh1.advertise<exercise_00::VidInfo>("VidInfo",100);
	exercise_00::VidInfo vidinfo_msg;
	
	sensor_msgs::ImagePtr msg1;
	Mat frame;	

	// int fourcc = VideoWriter::fourcc('D','I','V','X');
	// VideoWriter outputvideo("/home/out__put.avi", fourcc, 30, Size(1280,720));

	// usbcam -> video0 
	// laptop cam -> video 2

	VideoCapture cap1(0); 

	// cap1.open(0);
	int w = cap1.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	int h = cap1.set(cv::CAP_PROP_FRAME_HEIGHT, 720);	

	ros::Rate loop_rate(50);
	
	while (ros::ok())
	{
		// cap1.read(frame);
		waitKey(1);
		cap1 >> frame;

		// outputvideo.write(frame);

		msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
		image_raw_pub.publish(msg1);
		VidInfo.publish(VidInfoWrite(cap1, vidinfo_msg));
		
		
		
		imshow("frame1",frame);
		// waitKey(1);
		
		if (!cap1.isOpened())
		{
			cerr << "finish!\n" << endl;
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	// outputvideo.release();

	return 0;
}
