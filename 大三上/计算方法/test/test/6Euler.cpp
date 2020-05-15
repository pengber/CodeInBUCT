/*
*Ahthor:	Pengber
*Date:		2019年11月14日
*Question:	给定一阶导数（由程序内df函数指定），起始点的坐标，目标位置的横坐标和步长（输入），计算出该区间位置
*/
#include <stdio.h>
#define MAXSIZE 10000

double df(double x, double y);

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
	for (int i = 0; i < num; i++) {
		x[i + 1] = x[i] + h;//这里可以用两个线程算
		y[i + 1] = y[i] + h * df(x[i], y[i]);
	}
	for (int i = 0; i <= num; i++) {
		printf("x[%d]=%lf,y[%d]=%lf\n", i,x[i],i, y[i]);
	}
	return 0;
}

//f(x)的导数
double df(double x, double y) {
	return y - 2 * x / y;
}



/*以下是第一次打的代码：
缺点：
	没有将点和值保存，如果以后有函数要用到的话需要更改源码
	将其更改为向后差商代替导数或者步长为2的欧拉公式需要作较大的变动，没有用到循环本身具有的迭代性质。
int main() {
	double x0, y0, x1,y1, h;//x0,y0为已知点,x1,y1为下次迭代结果，h为步长
	double _x;//要计算到那个位置的横坐标
	long num;
	printf("\nPlease input the coordinates of ponit like 0 1:");
	scanf("%lf %lf", &x0, &y0);
	printf("\nPlease input the step(h):");
	scanf("%lf", &h);
	printf("\nPlease input the x-coordinate of target point:");
	scanf("%lf", &_x);
	num = (long)((_x - x0) / h);
	for (int i = 0; i < num; i++) {
		y1 = y0 + h * df(x0, y0);
		y0 = y1;
		x0 = x0 + h;
		printf("\nx[%d]=%lf,y[%d]=%lf", i+1, x0, i+1, y0);
	}
	return 0;
}

//f(x)的导数
double df(double x, double y) {
	return y - 2 * x / y;
}
*/