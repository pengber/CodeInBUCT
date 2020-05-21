#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat M(3, 2, CV_8UC3, Scalar(255)); 
	cout << "M = " << endl << " " << M << endl;

	system("pause");
}