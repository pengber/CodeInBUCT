#include <iostream> 
#include "opencv2/opencv.hpp" 

using namespace std; 
using namespace cv;

int main() {
	Mat im = imread("d:\\c++learning\\cv\\images\\lena.tif");
	Mat result;
	Canny(im, result, 50, 150);
	imwrite("d:\\c++learning\\cv\\images\\lena-canny.png", result);

	return 0;
}