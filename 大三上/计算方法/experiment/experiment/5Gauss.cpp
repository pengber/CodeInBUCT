//线性方程组直接求解，高斯消元法，列主元
#include <stdio.h>
using namespace std;
#define MAXSIZE 50	
void input(double a[MAXSIZE][MAXSIZE + 2], long degree) {
	for (int i = 0; i < degree; i++) {
		for (int j = 0; j <= degree; j++) {
			scanf("%lf", &a[i][j]);
		}
	}
}
void output(double x[MAXSIZE], long degree) {
	printf("The result vector is:");
	for (int i = 0; i < degree; i++) {
		printf("%lf ", x[i]);
	}
}
int main() {
	double a[MAXSIZE][MAXSIZE + 2], x[MAXSIZE], s;
	long i, j, k, degree;
	printf("Please input the degree of MATRIX:\n");
	scanf("%ld", &degree);
	printf("Please input the matrix[degree][degree+1]:\n");
	input(a, degree);

	for (k = 0; k < degree-1/*而不是degree*/; k++) {//n-1次循环
		for (i = k + 1; i < degree; i++) {//控制行数
			a[i][k] /= -a[k][k];
			for (j = k + 1; j < degree + 1; j++) {/*而不是degree,因为下标为degree的也要这样，也就是等式右边的那个*/
				a[i][j] += a[i][k] * a[k][j];
			}
		}
	}
	for (k = degree - 1; k >= 0; k--) {
		s = 0;
		for (i = k + 1; i < degree; i++) {
			s += x[i] * a[k][i];
		}
		x[k] = (a[k][degree] - s) / a[k][k];
		
	}
	output(x, degree);
	return 0;
}