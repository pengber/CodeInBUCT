#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

typedef struct _imgPair {
	Mat* src;
	Mat* dst;
	void* Param;
	char* winName;
}ImgPair;

typedef struct _gaussianParam {
	int kernelSize;
	int sigma;
}GaussianParam;

typedef struct _bilateralParam {
	int kernelSize;
	int sigmaColor;
	int sigmaSpace;
}BilateralParam;

void on_gaussiankernelBar(int ksize, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;
	GaussianParam* gPair = (GaussianParam*)(pImgPair->Param);
	gPair->kernelSize = ksize;

	GaussianBlur(*(pImgPair->src), *(pImgPair->dst), Size(gPair->kernelSize / 2 * 2 + 1, gPair->kernelSize / 2 * 2 + 1), gPair->sigma, gPair->sigma);
	imshow(pImgPair->winName, *(pImgPair->dst));
}


void on_gaussianSigmaBar(int sigma, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;
	GaussianParam* gPair = (GaussianParam*)(pImgPair->Param);
	gPair->sigma = double(sigma);

	GaussianBlur(*(pImgPair->src), *(pImgPair->dst), Size(gPair->kernelSize / 2 * 2 + 1, gPair->kernelSize / 2 * 2 + 1), gPair->sigma, gPair->sigma);
	imshow(pImgPair->winName, *(pImgPair->dst));
}




void on_medianSigmaBar(int ksize, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;

	medianBlur(*(pImgPair->src), *(pImgPair->dst), ksize / 2 * 2 + 1);
	imshow(pImgPair->winName, *(pImgPair->dst));

}


void on_bilateralDBar(int ksize, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;
	BilateralParam* param = (BilateralParam*)(pImgPair->Param);
	bilateralFilter(*(pImgPair->src), *(pImgPair->dst), ksize / 2 * 2 + 1, param->sigmaColor, param->sigmaSpace);
	param->kernelSize = ksize;
	imshow(pImgPair->winName, *(pImgPair->dst));

}



void on_bilateralSigmaSpaceBar(int sigmaSpace, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;
	BilateralParam* param = (BilateralParam*)(pImgPair->Param);
	bilateralFilter(*(pImgPair->src), *(pImgPair->dst), param->kernelSize / 2 * 2 + 1, param->sigmaColor, sigmaSpace);
	param->sigmaSpace = sigmaSpace;
	imshow(pImgPair->winName, *(pImgPair->dst));
}

void on_bilateralSigmaColorBar(int sigmaColor, void* userdata)
{
	ImgPair* pImgPair = (ImgPair*)userdata;
	BilateralParam* param = (BilateralParam*)(pImgPair->Param);
	bilateralFilter(*(pImgPair->src), *(pImgPair->dst), param->kernelSize / 2 * 2 + 1, sigmaColor, param->sigmaSpace);
	param->sigmaColor = sigmaColor;
	imshow(pImgPair->winName, *(pImgPair->dst));
}


int main()
{
	Mat src = imread("D:\\C++learning\\cv\\images\\683_488.bmp");

	namedWindow("src");
	imshow("src", src);


	/*-------GaussianBlur-----------*/
	Mat GaussianBlurImg;
	namedWindow("GaussianBlurImg");
	GaussianParam gaussianParam = { 5, 1.0 };
	GaussianBlur(src, GaussianBlurImg, Size(5, 5), 1, 1);
	GaussianParam gparam = { 5, 1.0 };
	ImgPair  gaussianPair = { &src, &GaussianBlurImg, &gparam,  (char*)"GaussianBlurImg" };

	imshow("GaussianBlurImg", GaussianBlurImg);
	createTrackbar("kernelsize", "GaussianBlurImg", &(gparam.kernelSize), 30, on_gaussiankernelBar, &gaussianPair);
	createTrackbar("sigma", "GaussianBlurImg", &(gparam.kernelSize), 10, on_gaussianSigmaBar, &gaussianPair);

	/*-------medianBlur-----------*/
	Mat MedianBlurImg;
	int kernelSize = 5;
	ImgPair  medianPair = { &src, &MedianBlurImg, nullptr,   (char*)"MedianBlurImg" };
	medianBlur(src, MedianBlurImg, 5);
	imshow("MedianBlurImg", MedianBlurImg);
	createTrackbar("kernelsize", "MedianBlurImg", &(kernelSize), 30, on_medianSigmaBar, &medianPair);


	/*---Bilateral-----------------*/
	Mat BilateralFilterImg;
	bilateralFilter(src, BilateralFilterImg, 5, 2, 2);
	BilateralParam bparam = { 5,1,1 };
	ImgPair  bilateralPair = { &src, &BilateralFilterImg, &bparam,   (char*)"BilateralFilterImg" };
	imshow("BilateralFilterImg", BilateralFilterImg);
	createTrackbar("kernelsize", "BilateralFilterImg", &(bparam.kernelSize), 30, on_bilateralDBar, &bilateralPair);
	createTrackbar("sigmaspace", "BilateralFilterImg", &(bparam.sigmaSpace), 30, on_bilateralSigmaSpaceBar, &bilateralPair);
	createTrackbar("sigmacolor", "BilateralFilterImg", &(bparam.sigmaColor), 30, on_bilateralSigmaColorBar, &bilateralPair);
	waitKey(0);
}
