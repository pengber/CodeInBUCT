/*
建立时间：2019/10/28
程序目标：改变指定图片的对比度，饱和度，亮度
*/
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int alpha; /**< 控制对比度 */
int beta;  /**< 控制亮度 */
Mat image;
Mat new_image;
string dstName = "dstImage";
void ChangeImage(int,void*);
int main()
{


	image = imread("../../images/lena.tif", IMREAD_UNCHANGED);
	if (image.empty()) {
		cout << "图像加载失败" << endl;
	}
	// 初始化  
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: ";
	cin >> alpha;
	cout << "* Enter the beta value [0-100]: ";
	cin >> beta;
    new_image = Mat::zeros(image.size(), image.type());

	namedWindow(dstName, 1);
	createTrackbar("contrast:", dstName, &alpha, 100, ChangeImage);
	
	
	waitKey();
	return 0;
}

void ChangeImage(int, void*) {
	namedWindow("a", 1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				new_image.at<Vec3b>(i, j)[k] =
					saturate_cast<uchar>(alpha *0.01 * (image.at<Vec3b>(i, j)[k]) + beta);
				//saturate_cast用于溢出保护，如果大于255的话则置为255（假设255为最大有效值）
			}
		}
	}
	imshow(dstName, new_image);
}