//解决数值积分问题
#include <stdio.h>
#include <math.h>
#define MAXSIZE 7

void input(double* y, double a, double b, int n) {//n个节点
	for (int i = 0; i < n; i++) {
		printf("\nPlease input the y[%d] of pair:", i);
		scanf("%lf", &y[i]);
	}
}
void compute(double* y, double a, double b, int n) {
	double h = (b - a) / (n - 1);
	double x = a;
	//y[0] = 1;
	//x += h;
	for (int i = 0; i < n; i++) {															
		////y[i] = sqrt(4 - sin(x)*sin(x));
		//y[i]  = sin(x) / x;
		//y[i] = sqrt(x);
		//y[i] = exp(2) / (4 + x * x);
		y[i] = log(1 + x) / (1 + x * x);
		x += h;
	}

}
int main() {
	long c[MAXSIZE][MAXSIZE / 2 + 2] = { {2, 1}, {6, 1, 4}, {8, 1, 3}, {90, 7, 32, 12},
		{288, 19, 75, 50}, {840, 41, 216, 27, 272}, {17280, 751, 3577, 1323, 2989}
	};
	double y[MAXSIZE], a, b, integral = 0;
	int i, j, n;
	printf("Please input the num(2~7) a b divided by space:\n");
	scanf("%d %lf %lf", &n, &a, &b);
	//input(y, a, b, n);
	compute(y, a, b, n);
	for (i = 0; i < n / 2; i++){
		//错误代码integral += (y[i] + y[n - 1 - i])* c[i][n / 2 + 2] / c[i][0];
		integral += (y[i] + y[n - 1 - i]) * c[n-2][i+1] / c[n-2][0];//横坐标：n个节点，n-1阶公式，下标n-2;纵坐标：0存储分母，i+1存储对称的1-n/2个分子
	}
	if (n % 2) {
		integral += (y[n / 2]) * c[n-2][n / 2 + 1] / c[n-2][0];//MAXSIZE/2+2是大小，那么因为对半存储那么最远的n/2+1即为中心点
	}
	integral *= b - a;
	printf("%lf", integral);
	return 0;
}