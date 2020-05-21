/*this program is to test convert of different color space
*/
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("../../images/50_50.bmp");

	//判断图像是否加载成功
	if (!srcImage.data)
	{
		cout << "图像加载失败!" << endl;
		return false;
	}
	else
		cout << "图像加载成功!" << endl << endl;

	//显示原图像
	namedWindow("srcImage", WINDOW_AUTOSIZE);
	imshow("srcImage", srcImage);

	//将图像转换为灰度图，采用CV_前缀
	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);     //将图像转换为灰度图
	namedWindow("grayImage", WINDOW_AUTOSIZE);
	imshow("grayImage", grayImage);

	//将图像转换为HSV，采用COLOR_前缀
	Mat HSVImage;
	cvtColor(srcImage, HSVImage, COLOR_BGR2HSV);    //将图像转换为HSV图
	namedWindow("HSV", WINDOW_AUTOSIZE);
	imshow("HSV", HSVImage);
	cout << HSVImage;
	waitKey(0);

	return 0;
}