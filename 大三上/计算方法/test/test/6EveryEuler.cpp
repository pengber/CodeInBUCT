/*
*Ahthor:	Pengber
*Date:		2019年11月14日
*Question:	给定一阶导数（由程序内df函数指定），起始点的坐标，目标位置的横坐标和步长（输入），计算出该区间位置
*Tips:		本程序实现步长为1，步长为2，改进的欧拉
*/
#include <stdio.h>
#include <malloc.h>//改进的欧拉算法中用来存储中间量y拔
#define MAXSIZE 10000

double df(double x, double y);
void print(double* x, double* y, long n);
void eulerStep1(double* x, double* y, double h, double _x);
void eulerStep2(double* x, double* y, double h, double _x);
void eulerStrong(double* x, double* y, double h, double _x);


int main() {
	double _x, h;//_x为目标出横坐标
	double x[MAXSIZE], y[MAXSIZE];
	long num;
	printf("\nPlease input the coordinates of ponit like 0 1:");
	scanf("%lf %lf", &x[0], &y[0]);
	printf("\nPlease input the step(h):");
	scanf("%lf", &h);
	printf("\nPlease input the x-coordinate of target point:");
	scanf("%lf", &_x);
	num = (long)((_x - x[0]) / h);
	if (num >= MAXSIZE) {
		printf("h is to big or x0 is too far with target-x");
		return 0;
	}
	printf("\neulerStep1 result is :");
	eulerStep1(x, y, h, _x);
	print(x, y, num);

	printf("\neulerStep2 result is :");
	eulerStep2(x, y, h, _x);
	print(x, y, num);

	printf("\neulerStrong result is:");
	eulerStrong(x, y, h, _x);
	print(x, y, num);
	
	return 0;
}

//f(x)的导数
double df(double x, double y) {
	return y - 2 * x / y;
}
//输出x0到目标x的以h为步长的点的坐标
void print(double* x, double* y,long n) {
	for (int i = 0; i <= n; i++) {
		printf("\nx[%d]=%lf,y[%d]=%lf", i, x[i], i, y[i]);
	}
}

void eulerStep1(double* x, double* y, double h, double _x) {
	long num = long((_x - x[0]) / h);
	for (int i = 0; i < num; i++) {
		x[i + 1] = x[i] + h;//这里可以用两个线程算
		y[i + 1] = y[i] + h * df(x[i], y[i]);
	}
}
void eulerStep2(double* x, double* y, double h, double _x) {
	long num = long((_x - x[0]) / h);
	x[1] = x[0] + h;
	y[1] = y[0] + h * df(x[0], y[0]);
	for (int i = 1; i < num; i++) {//从1开始
		x[i + 1] = x[i] + h;//这里可以用两个线程算
		y[i + 1] = y[i-1] + 2*h * df(x[i], y[i]);
	}
}
void eulerStrong(double* x, double* y, double h, double _x) {
	long num = long((_x - x[0]) / h);
	double* y_ = (double *)malloc(MAXSIZE * sizeof(double));
	for (int i = 0; i < num; i++) {
		x[i + 1] = x[i] + h;
		y_[i + 1] = y[i] + h * df(x[i], y[i]);//求得y拔
		y[i + 1] = y[i] + h / 2 * (df(x[i], y[i]) + df(x[i + 1], y_[i + 1]));
	}
	free(y_);
}
