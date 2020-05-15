//解决非线性方程求根问题
#include <stdio.h>
#include <math.h>
//#include <iostream>
//using namespace std;
//非线性方程x=f(x);
double f(double x);
//线性方程一次倒数;
double df(double x);

int main() {
	double x0, x1, fx0, dfx0, epsilon;
	long i, maxi;
	printf("Please input the suspision like 0.0001:\n");
	scanf("%lf", &epsilon);
	printf("Please input the times of compute like 1000:\n");
	scanf("%ld", &maxi);
	printf("Please input the inicial value of computing like 2:\n");
	scanf("%lf", &x1);//注意这里是x1,因为要在迭代里将x1赋值给x0

	for (i = 0; i < maxi; i++) {
		x0 = x1;
		fx0 = f(x0);// cout << i << ":" << fx0 << endl;
		dfx0 = df(x0);// cout << i << ":" << dfx0 << endl;
		x1 = x0 - fx0 / dfx0;
		if (fabs(x1 - x0) <= epsilon) {
			break;//精度达到要求跳出循环
		}
	}
	if (i <= maxi) {//源代码不对，最大迭代次数为1000时，i退出时为1000，0-999执行1000次最后+1判别推出循环
		printf("the result is %lf\n", x1);
	}
	else {
		printf("在迭代次数限制内未求得该精度的解!\n");
	}
	return 0;
}

double f(double x) {
	//return pow(x, 3) -x -1;//f(x)=x^3-x-1;ppt上例子
	//return pow(x, 2) - 2;//f(x) = x^2-a,也就是开方法是牛顿迭代法的特例
	//return x * exp(x) - 1;
	return x * x * x - 2 * x - 55;
}
double df(double x) {
	//return 3 * pow(x, 2) - 1;//df(x)=3*x^2-1;
	//return exp(x) + exp(x) * x;
	return 3 * x * x - 2;
}