#include<iostream>
using namespace std;

#define N 4

template<class T>
void difference(T* x, T* y, int n)
{
	float* chash = new float[n + sizeof(float)];
	for (int i = 1; i <= n; i++)    // 外层求差商
	{
		chash[0] = y[i];
		for (int j = 0; j < i; j++) {
			chash[j + 1] = (chash[j] - y[j]) / (x[i] - x[j]);   //把每次差商计算的值存到y中
		}
		chash[i] = y[i];            // 得到该阶的差商
	}
	for (int i = 0; i < n; i++)
		cout << y[i] << " ";
	cout << endl;
}

int main()
{
	int x[4] = { 0, 2, 3, 5 };
	int y[4] = { 1, 3, 2, 5 };
	difference(x, y, 3);
	return 0;
}