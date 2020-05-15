#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>
using namespace std;

#define N 5	//进程数量
#define M 3	//向量长度
#define random(x) rand() % x//随机测试产生数据
int num[M] = { 10, 5, 7 };//资源最大初始值
int Max[N][M] = { 0 };
int Allocation[N][M] = { 0 };
int Rest[M] = { 0 };//work和available
int Need[N][M] = { 0 };
void randTest();
void cinTest();
void getProcess(int* i, int* want);
/*银行家算法模块*/
bool compare(int* a, int* b);
void add(int* a, int* b);
int getProcess(int Need[N][M], int* Rest, bool* Finish);
void getRest();
bool safeTest();
void changeProcess(int i, int* want);
void backProcess(int i, int* want);
/*_______________*/
/*输出模块*/
void print(queue<int> a);
void printMatrix();
//~随机测试样例产生函数
void randTest() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int temp = random(num[j]);
			Max[i][j] = temp?temp:1;//对每个进程随机产生最大请求资源数（在已有的最大资源数范围内）并且如果为0的话置为1，因为下面的Allocation随机数用Max,0不能做除数。
			Allocation[i][j] = random(Max[i][j]/2);//Allocation可以为0,处以2是增加安全的概率
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}

	}
}
/*~输入样例：
每一行前三个是MAX，后三个是Allocation，自动计算need，共N=5个进程
7 5 3 0 1 0
3 2 2 2 0 0
9 0 2 3 0 2
2 2 2 2 1 1
4 3 3 0 0 2
*/
void cinTest() {
	int n = N;
	int m = M;
	cout << "process has" << n << ",source has " << m << ",Please input example data:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Max[i][j];
		}
		for (int j = 0; j < M; j++) {
			cin >> Allocation[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
}
//~输入进程号和进程请求的资源数目
void getProcess(int* i, int* want) {
	int temp;
	cout << "Please input processId" << endl;
	cin >> temp;
	//*i = temp;
	cout << "Please input vector factor:" << endl;
	for (int j = 0; j < M; j++) {
		cin >> want[j];
	}
	return;
}
/*******银行家算法模块*********************/
//~比较两向量对应位置，如果前一个向量的所有分量小于等于第二个分量，返回真
bool compare(int* a, int* b) {
	for (int j = 0; j < M; j++) {
		if (a[j] > b[j]) return false;
	}
	return true;
}
//~两长度为M的向量的相加并存储到第一个向量
void add(int* a, int* b) {
	for (int j = 0; j < M; j++) {
		a[j] += b[j];
	}
}
//~返回未完成并且Need小于Rest的进程好，没有返回-1
int getProcess(int Need[N][M], int* Rest,bool * Finish) {
	for (int i = 0; i < N; i++) {
		if (!Finish[i] && compare(Need[i], Rest)) return i;
	}
	return -1;
}
//~得到rest数组，也就是Work数组
void getRest() {
	for (int j = 0; j < M; j++) {
		Rest[j] = num[j];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Rest[j] -= Allocation[i][j];
		}
	}
}
bool safeTest() {
	bool Finish[N] = { false };
	queue<int> answer;
	int index = getProcess(Need, Rest, Finish);
	while (index != -1) {
		answer.push(index);
		Finish[index] = true;
		add(Rest, Allocation[index]);
		index = getProcess(Need, Rest, Finish);
	}
	//_完成检测
	for (int i = 0; i < N; i++) {
		if (Finish[i] == false) {
			cout << "NOT SAFE!" << endl;
			print(answer);
			return false;
		}
	}
	//_如果FINITSH数组都是真的话，则安全，否则不安全，两者都输出现有的序列，用于观察
	cout << "SAFE!" << endl;
	print(answer);
	return true;
}

//~改变进程号和请求资源数
void changeProcess(int i, int* want) {
	for (int j = 0; j < M; j++) {
		Allocation[i][j] += want[j];
		Need[i][j] -= want[j];
	}
}

void backProcess(int i, int* want) {
	for (int j = 0; j < M; j++) {
		Allocation[i][j] -= want[j];
		Need[i][j] += want[j];
	}
}

/*_______________银行家算法模块end___________________*/
/*********************输出模块*********************/
//~形参安全序列，输出安全序列
void print(queue<int> a) {
	int index;
	int length = a.size();
	cout << "safe queue is:";
	for (int i = 0; i < length; i++) {
		index = a.front();
		a.pop();
		cout << index << " ";
	}
	cout << endl;
}
//~输出三大Max,Allocation,Need和Rest向量组
void printMatrix() {
	cout << setw(M * 5) << "Max|";
	cout << setw(M * 5) << "Allocation|";
	cout << setw(M * 5) << "Need Matrix|" << endl;
	for (int i = 0; i < N; i++) {
		
		for (int j = 0; j < M; j++) {
			cout << setw(5) << Max[i][j];
		}

		for (int j = 0; j < M; j++) {
			cout << setw(5) << Allocation[i][j];
		}
		for (int j = 0; j < M; j++) {
			cout << setw(5) << Need[i][j];
		}
		cout << endl;
	}
	cout << "Rest is" << endl;
	for (int j = 0; j < M; j++) {
		cout << setw(5) << Rest[j];
	}
	cout << endl;
}
/*_____________________输出模块end___________________________*/
int main() {
	srand((int)time(0));
	//randTest();
	cinTest();

	//_初始化数据完毕
	getRest();
	//_得到Available/Work数组（Rest)
	
	if (safeTest()) {//如果安全的话可以进行一次进程调用的模拟，如果多次可以用while或者递归
		printMatrix();
		int pro = 0;
		int want[M] = { 0 };
		getProcess(&pro, want);
		for (int j = 0; j < M; j++) {
			if (compare(want, Need[pro]));
			else {
				cout << "source num is wrong! someone bigger than need";
				return 0;
			}
			if (compare(want, Rest));
			else {
				cout << "source num is wrong! someone bigger than rest!";
				return 0;
			}
		}
		getRest();
		safeTest();
		printMatrix();
	}

	return 0;
}
