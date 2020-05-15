#include <stdio.h>

#define MAXSIZE 50

void input(double* x, double* y,int n) {
	for (int i = 0; i < n; i++) {
		printf("\nplease input x[%d],y[%d]:", i, i);
		scanf("%lf %lf", &x[i], &y[i]);
	}
}

int main() {
	double x[MAXSIZE], y[MAXSIZE], _x,_y;//t为double
	int i, j, num,t;
	printf("Please input num of interpolation node:");
	scanf("%d", &num);//插值节点的个数
	input(x, y, num);
	printf("\nPlease input x of interpolation node:");//输入插值节点的根坐标
	scanf("%lf",&_x);
	_y = 0;//因为迭代为+=
	//Lagrange interpolation
	for (i = 0; i < num; i++) {
		t = 1;
		for (j = 0; j < num; j++) {
			if (i != j) t = t * (_x - x[j]) / (x[i] - x[j]);
		}
		_y += t*y[i];
	}
	printf("\nthe y of interpolation node is:%lf", _y);
	return 0;
}