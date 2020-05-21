#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"  //图像处理模块
#include <iostream>

using namespace cv;
using namespace std;


int alpha;
Mat src;
Mat bgr;
Mat hsv;
Mat dst;
string windowName = "src";
string hsvName = "hsv";
string dstName = "dst";
void ChangeImage(int, void*);
int main() {
	alpha = 80;
	src = imread("../../images/lena.tif");
	dst = Mat::zeros(src.size(), src.type());
	if (src.empty()) {
		cout << "srcImage reading failed!" << endl;
	}
	namedWindow(windowName, WINDOW_AUTOSIZE);
	imshow(windowName, src);

	src.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	namedWindow(hsvName, WINDOW_GUI_EXPANDED);
	imshow(hsvName, hsv);

	namedWindow(dstName, 1);
	createTrackbar("contrast:", dstName, &alpha, 1000, ChangeImage);
	
	//ChangeImage(alpha, 0);
	waitKey(0);
}

void ChangeImage(int, void*) {
	for (int i = 0; i < hsv.rows; i++)
	{
		for (int j = 0; j < hsv.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				dst.at<Vec3b>(i, j)[k] =
					alpha * 0.01 * (hsv.at<Vec3b>(i, j)[k]);
				//saturate_cast用于溢出保护，如果大于255的话则置为255（假设255为最大有效值）
			}
		}
	}
	imshow(dstName, dst);
	
}