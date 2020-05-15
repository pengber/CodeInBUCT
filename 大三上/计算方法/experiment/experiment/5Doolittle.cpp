//线性方程组的迭代法
#include <stdio.h>
#define MAXSIZE 50

void input(double a[][MAXSIZE], double* b, long degree) {
	for (long i = 0; i <= degree - 1; i++) {
		for (long j = 0; j <= degree - 1; j++) {
			scanf("%lf", &a[i][j]);
		}
		scanf("%lf", &b[i]);
	}
}
void output(double* x, long degree) {
	for (long i = 0; i <= degree - 1; i++) {
		printf("%lf\n", x[i]);
	}
}
int main() {
	double a[MAXSIZE][MAXSIZE],b[MAXSIZE],x[MAXSIZE],y[MAXSIZE], L[MAXSIZE][MAXSIZE], U[MAXSIZE][MAXSIZE];
	long i, j, k,degree;
	printf("Please input the degree of matrix:");
	scanf("%ld", &degree);

	printf("\nPlease input the matrix:");
	input(a, b, degree);
	for (i = 0; i < degree; i++) {
		L[i][i] = 1;
	}
	for (i = 0; i < degree; i++) {
		for (j = i; j < degree; j++) {
			U[i][j] = a[i][j];
			for (k = 0; k <= i - 1; k++) {
				U[i][j] -= (L[i][k] * U[k][j]);
			}
		}
		for (j = i + 1; j < degree; j++) {
			L[j][i] = a[j][i];
			for (k = 0; k <= i - 1; k++) {
				L[j][i] -= (L[j][k] * U[k][i]);
			}
			L[j][i] /= U[i][i];
		}
	}

	for (i = 0; i < degree; i++) {
		y[i] = b[i];
		for (j = 0; j < i; j++) {
			y[i] -= (L[i][j] * y[j]);
		}
	}//因为L[i][i]为1，所以除以相当于不除

	for (i = degree - 1; i >= 0; i--) {
		x[i] = y[i];
		for (j = i+1; j < degree; j++) {
			x[i] -= (U[i][j] * x[j]);
		}
		x[i] /= U[i][i];
	}
	printf("The result vector is:\n");
	output(x, degree);
	
	return 0;
}