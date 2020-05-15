//非线性方程求根问题，牛顿法的改进
#include <stdio.h>
#include <math.h>

//非线性方程x=f(x);
double f(double x);
//线性方程一次倒数;
double df(double x);

int main() {
	double x0, x1, fx0, dfx0, epsilon;
	long i, maxi;
	double lamda = 1;
	printf("请输入精度，例如：0.0001，:\n");
	scanf("%lf", &epsilon);
	printf("请输入最大迭代次数，例如：1000，：\n");
	scanf("%ld", &maxi);
	printf("请输入迭代初值，例如：2，：\n");
	scanf("%lf", &x1);//注意这里是x1,因为要在迭代里将x1赋值给x0
	
	for (i = 0; i < maxi; i++) {
		x0 = x1;
		fx0 = f(x0);
		dfx0 = df(x0);
		x1 = x0 - lamda*fx0 / dfx0;
		if (fabs(f(x1)) < fabs(f(x0))) lamda = 1;
		else {
			x1 = x0;
			lamda /= 2;
			i--;//保持迭代次数不变，本次循环只用来求lamda
			continue;//必须加这行进行下一次迭代，否则x0=x1退出循环
		}
		if (fabs(x1 - x0) <= epsilon) {
			break;//精度达到要求跳出循环
		}
	}
	if (i <= maxi) {//源代码不对，最大迭代次数为1000时，i退出时为1000，0-999执行1000次最后+1判别推出循环
		printf("解为%lf\n", x1);
	}
	else {
		printf("在迭代次数限制内未求得该精度的解!\n");
	}
	return 0;
}

double f(double x) {
	return pow(x, 3) -x -1;//f(x)=x^3-x-1;ppt上例子
	//return pow(x, 2) - 2;//f(x) = x^2-a,也就是开方法是牛顿迭代法的特例
}
double df(double x) {
	return 3 * pow(x, 2) - 1;//df(x)=3*x^2-1;
	//return 2 * x;
}