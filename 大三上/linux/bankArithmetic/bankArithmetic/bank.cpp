#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;

#define N 5
#define M 3
#define random(x) rand() % x
int Max[N][M] = { 0 };
int Allocation[N][M] = { 0 };
int Need[N][M] = { 0 };
//比较两向量对应位置，如果前一个向量的所有分量小于等于第二个分量，返回真
bool compare(int* a, int* b) {
	for (int j = 0; j < M; j++) {
		if (a[j] > b[j]) return false;
	}
	return true;
}
//两长度为M的向量的相加并存储到第一个向量
void add(int* a, int* b) {
	for (int j = 0; j < M; j++) {
		a[j] += b[j];
	}
}
//返回未完成并且Need小于Rest的进程好，没有返回-1
int getProcess(int Need[N][M], int* Rest,bool * Finish) {
	for (int i = 0; i < N; i++) {
		if (!Finish[i] && compare(Need[i], Rest)) return i;
	}
	return -1;
}
int main() {
	int num[M] = {10, 5, 7 };
	srand((int)time(0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Max[i][j] = random(num[j]);//对每个进程随机产生最大请求资源数（在已有的最大资源数范围内）
			Allocation[i][j] = random(num[j] / 2);
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	//_初始化数据完毕
	int Rest[M] = { 0 };//work和available
	bool Finish[M] = { false };
	for (int j = 0; j < M; j++) {
		Rest[j] = num[j];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Rest[j] -= Allocation[i][j];
		}
	}
	//_得到Available数组
	int index = getProcess(Need,Rest,Finish);
	while (index) {
		Finish[index] = true;
		add(Rest, Allocation[index]);
		index = getProcess(Need, Rest, Finish);
	}
	//_完成检测
	bool flag = true;
	for (int j = 0; j < M; j++) {
		flag = flag && Finish[j];
	}

	if (flag) {
		cout << "safe";
	}
	else {
		cout << "not safe";
	}
	/*int i;
	int want[M] = { 0 };
	cin >> i;
	for (int i = 0; i < M; i++) {
		cin >> want[i];
	}*/

	return 0;
}