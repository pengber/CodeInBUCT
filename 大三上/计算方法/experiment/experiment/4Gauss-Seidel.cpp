//线性方程组迭代法
#include <stdio.h>
#include <cmath>
#define MAXSIZE 50

void input(double a[][MAXSIZE], double* b, long degree) {
	for (int i = 0; i <= degree-1; i++) {
		for (int j = 0; j <= degree - 1; j++) {
			scanf("%lf", &a[i][j]);
		}
		scanf("%lf", &b[i]);
	}
}
void output(double* x, long degree) {
	for (int i = 0; i <= degree - 1; i++) {
		printf("%lf", x[i]);
	}
}
int main() {
	double a[MAXSIZE][MAXSIZE], b[MAXSIZE], x[MAXSIZE];//存储矩阵系数，值向量，解向量
	double epsilon, e,s,old;//存储代数精度和产生的代数精度,s为中间变量.old存放
	long max, i, j, k, degree;//存储最大迭代次数，循环控制变量，阶数

	printf("Please input the degree of matrix:");
	scanf("%ld", &degree);

	printf("\nPlease input the matrix:");
	input(a, b,degree);

	printf("\nPlease input the inital vector:");
	for (i = 0; i <= degree - 1; i++) {
		scanf("%lf", &x[i]);
	}
	printf("\nPlease input the epsilon:");
	scanf("%lf", &epsilon);

	printf("\nPlease input the max times of iteration:");
	scanf("%ld", &max);

	for (k = 0; k < max; k++) {
		e = 0;								//控制最晚精确度到epsilon的那个x，
		for (i = 0; i <= degree - 1; i++) {
			old = x[i];
			s = 0;
			for (j = 0; j <= degree - 1; j++) {
				if (j != i) s += a[i][j] * x[j];
			}
			x[i] = (b[i] - s) / a[i][i];
			if (fabs(x[i] - old) > e) {//如果哪个函数值代数精度比其他的函数值的代数精度大，则替换e
				e = fabs(x[i] - old);
			}
		}
		for (int z = 0; z < degree; z++) {
			printf("%lf ", x[z]);
		}
		printf("\n");
		if (e < epsilon) break;//如果最迟钝的x的代数精度都小于epsilon,则达到要求
	
	}
	output(x, degree);
	return 0;
}