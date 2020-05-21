#include <iostream>
#include "opencv2/opencv.hpp" 
#include "opencv2/imgproc/types_c.h"

using namespace std; using namespace cv;

int main(int argc, char** argv) {
	//打开第一个摄像头     
	VideoCapture cap(0); 

	//打开视频文件     
	//VideoCapture cap("video.short.raw.avi");

	//检查是否成功打开     
	if (!cap.isOpened()) {
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}

	Mat edges;

	//创建窗口     
	namedWindow("edges", 1);

	for (;;) {
		Mat frame;         //从 cap 中读一帧，存到 frame         
		cap >> frame;         //如果未读到图像         
		if (frame.empty())
			break;
		//将读到的图像转为灰度图         
		cvtColor(frame, edges, CV_BGR2GRAY);
		//进行边缘提取操作         
		Canny(edges, edges, 0, 30, 3);
		//显示结果         
		imshow("edges", edges);
		//等待 30 秒，如果按键则推出循环         
		if (waitKey(30) >= 0)
			break;
	}
	//退出时会自动释放 cap 中占用资源     
	return 0;

}