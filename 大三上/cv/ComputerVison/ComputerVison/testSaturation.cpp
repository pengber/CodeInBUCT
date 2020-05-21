#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "HSL.hpp"

using namespace std;
using namespace cv;

static string window_name = "photo";
static Mat src;

static HSL hsl;
static int color = 0;
static int hue = 180;
static int saturation = 100;
static int brightness = 100;

static void callbackAdjust(int, void*)
{
	Mat dst;

	hsl.channels[color].hue = hue - 180;
	hsl.channels[color].saturation = saturation - 100;
	hsl.channels[color].brightness = brightness - 100;

	hsl.adjust(src, dst);

	imshow(window_name, dst);
}

static void callbackAdjustColor(int, void*)
{
	hue = hsl.channels[color].hue + 180;
	saturation = hsl.channels[color].saturation + 100;
	brightness = hsl.channels[color].brightness + 100;

	setTrackbarPos("hue", window_name, hue);
	setTrackbarPos("saturation", window_name, saturation);
	setTrackbarPos("brightness", window_name, brightness);
	callbackAdjust(0, 0);
}


int main()
{
	src = imread("building.jpg");

	if (!src.data) {
		cout << "error read image" << endl;
		return -1;
	}

	namedWindow(window_name);
	createTrackbar("color", window_name, &color, 6, callbackAdjustColor);
	createTrackbar("hue", window_name, &hue, 2 * hue, callbackAdjust);
	createTrackbar("saturation", window_name, &saturation, 2 * saturation, callbackAdjust);
	createTrackbar("brightness", window_name, &brightness, 2 * brightness, callbackAdjust);
	callbackAdjust(0, 0);

	waitKey();
	return 0;

}