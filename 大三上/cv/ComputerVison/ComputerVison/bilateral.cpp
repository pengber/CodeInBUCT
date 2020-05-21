#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<ctime>
#include <math.h>
#include <algorithm>
#include <iostream>

double** darr;
double* rarr;
using namespace cv;
using namespace std;

double ** getGuassionArray(int size, double sigma) {
	int i, j;
	double sum = 0.0;
	int center = size/2; //以第一个点的坐标为原点，求出中心点的坐标，center为半径
	double** arr = new double*[size];
	for (int k = 0; k < size; k++) {
		arr[k] = new double[size];
	}
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j) {
			arr[i][j] = exp(-((i - center) * (i - center) + (j - center) * (j - center)) / (sigma * sigma * 2));
			sum += arr[i][j];
		}
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
			arr[i][j] /= sum;
	return arr;
}

double *getRangeArray(int size, double sigma) {
	double* arr = new double(256);
	for (int i = 0; i < 256; i++) {
		arr[i] = exp(-(long( i * i) / (sigma * sigma * 2)));
	}
	return arr;
	
}
void salt(Mat& image, int num) {
	if (!image.data) return;//防止传入空图
	int i, j;
	srand(time(NULL));
	for (int x = 0; x < num; ++x) {
		i = rand() % image.rows;
		j = rand() % image.cols;
		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}
}

void myBilateral(const Mat _src, Mat& _dst,int size) {
	if (!_src.data) return;

	int kernal = size / 2;
	darr = getGuassionArray(size, 1);//自定义得到的权值数组
	rarr = getRangeArray(size, 1);
	
	Mat tmp(_src.size(), _src.type());
	for (int i = 0; i < _src.rows; ++i) {
		for (int j = 0; j < _src.cols; ++j) {
			//边缘不进行处理
			for (int k = 0; k < 3; k++) {
				if ((i - 1) > 0 && (i + 1) < _src.rows && (j - 1) > 0 && (j + 1) < _src.cols) {
					//对三通道进行处理

						//对核进行移动
					double weight_sum = 0;
					double pixcel_temp = 0;
					for (int x = 0; x < size; ++x) {
						for (int y = 0; y < size; ++y) {

							int pixcel_dif = (int)abs(_src.at<Vec3b>(i - 1 + x, j - 1 + y)[k] - _src.at<Vec3b>(i, j)[k]);
							double weight_temp = darr[x][y] * rarr[pixcel_dif];
							pixcel_temp += _src.at<Vec3b>(i, j)[k] * weight_temp;
							weight_sum += weight_temp;

						}

						pixcel_temp /= weight_sum;
						tmp.at<Vec3b>(i, j)[k] = pixcel_temp;
					}

				}
				else {
					tmp.at<Vec3b>(i, j)[k] = _src.at<Vec3b>(i, j)[k];
				}
			}
		}
	}

	tmp.copyTo(_dst);
}

void main() {
	Mat image = imread("../../images/lena.tif");
	Mat salt_image;
	image.copyTo(salt_image);
	imshow("source_image", image);
	Mat _gaussian;
	Mat image1;
	salt(salt_image, 1000);
	myBilateral(salt_image, _gaussian,3);

	
	imshow("salt_image", salt_image);
	imshow("opencv_gaussian_filtering", image1);
	imshow("my_filtering", _gaussian);
	waitKey();
}