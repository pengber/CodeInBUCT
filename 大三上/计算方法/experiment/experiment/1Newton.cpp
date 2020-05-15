//解决插值问题
#include <stdio.h>

#define MAXSIZE 30

void input(double diff[][MAXSIZE], int n) {
	for (int i = 0; i < n; i++) {
		printf("\nplease input x[%d],y[%d]:", i, i);
		scanf("%lf %lf", &diff[i][0], &diff[i][1]);
	}
}
void difference(double diff[][MAXSIZE], int n) {	//n个样本点
	for (int j = 2; j < n + 1; j++) {				//从第1阶（列下标2）差值计算，计算到n-1阶（列下标n)
		for (int i = j - 1; i < n; i++) {
			//diff[i][j] = (diff[i][j - 1] - diff[i - 1][j - 1]) / (diff[i][0] - diff[i - 1][0]);//注意除数，这行是错误的
			diff[i][j] = (diff[i][j - 1] - diff[i - 1][j - 1]) / (diff[i][0] - diff[i - (j - 1)][0]);
		}
	}
}
void printDiff (double diff[][MAXSIZE], int n) {//显示差分表
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			printf("%lf ", diff[i][j]);
		}
		printf("\n");
	}
}
int main() {
	double diff[MAXSIZE][MAXSIZE] = { 0 }, _x, _y;//t为double，差值表是一个n行n+1列的二维表
	int i, j, num;							//num个样本点
	double t;								//注意t是double类型。
	printf("Please input num of interpolation node:");
	scanf("%d", &num);//插值节点的个数
	input(diff, num);
	printf("\nPlease input x of interpolation node:");//输入插值节点的根坐标
	scanf("%lf", &_x);
	difference(diff,num);
	printDiff(diff, num);
	_y = 0;
	for (i = 0; i < num; i++) {
		t = 1;
		for (j = 0; j < i; j++) {
			t *= (_x - diff[j][0]);//计算插值基函数
		}
		_y += (t * diff[i][i + 1]);
	}
	
	printf("\nthe y of interpolation node is:%lf", _y);
	return 0;
}