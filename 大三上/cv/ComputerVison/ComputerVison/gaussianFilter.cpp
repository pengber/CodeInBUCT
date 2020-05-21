#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<ctime>
using namespace cv;
using namespace std;

double** getGuassionArray(int size, double sigma) {
	int i, j;
	double sum = 0.0;
	int center = size; //以第一个点的坐标为原点，求出中心点的坐标

	double** arr = new double* [size];//建立一个size*size大小的二维数组
	for (i = 0; i < size; ++i)
		arr[i] = new double[size];

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

void myGaussian(const Mat _src, Mat& _dst) {
	if (!_src.data) return;
	double** arr;
	Mat tmp(_src.size(), _src.type());
	for (int i = 0; i < _src.rows; ++i)
		for (int j = 0; j < _src.cols; ++j) {
			//边缘不进行处理
			if ((i - 1) > 0 && (i + 1) < _src.rows && (j - 1) > 0 && (j + 1) < _src.cols) {
				arr = getGuassionArray(3, 1);//自定义得到的权值数组
				tmp.at<Vec3b>(i, j)[0] = 0;
				tmp.at<Vec3b>(i, j)[1] = 0;
				tmp.at<Vec3b>(i, j)[2] = 0;
				for (int x = 0; x < 3; ++x) {
					for (int y = 0; y < 3; ++y) {
						tmp.at<Vec3b>(i, j)[0] += arr[x][y] * _src.at<Vec3b>(i + 1 - x, j + 1 - y)[0];
						tmp.at<Vec3b>(i, j)[1] += arr[x][y] * _src.at<Vec3b>(i + 1 - x, j + 1 - y)[1];
						tmp.at<Vec3b>(i, j)[2] += arr[x][y] * _src.at<Vec3b>(i + 1 - x, j + 1 - y)[2];
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

	Mat _gaussian;
	Mat image1;
	salt(salt_image, 1000);
	myGaussian(salt_image, _gaussian);
	GaussianBlur(salt_image, image1, Size(3, 3), 1);

	imshow("source_image", image);
	imshow("salt_image", salt_image);
	imshow("opencv_gaussian_filtering", image1);
	imshow("my_filtering", _gaussian);
	waitKey();
}