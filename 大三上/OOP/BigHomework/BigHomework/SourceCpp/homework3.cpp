#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

#define NUM 5	//cash容量
#define SUM 40	//需要调度的页面数量
#define PAGE_NUM 20	//页面号范围
#define random(x) (rand()%x)
class pageClass {
public: 
		int num;
		int time;		//每个页面的页面号和时间
};

pageClass pages[SUM];
int cash[NUM][SUM];	//存放页面的调度顺序，列为此时存在的页面序号，行代表时间
int	queue[100];		//调入队列
int k = -1;				//调入队列下标

int init(pageClass* p, int c[NUM][SUM]) {
	int i, j;
	for (int i = 0; i < SUM; i++) {
		p[i].num = -1;
		p[i].time = i;		//初始时间不影响，只要不同即可
	}
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < SUM; j++) {
			c[i][j] = -1;
		}
	}
	return 0;
}

int getLong(pageClass* p) {
	int i;
	int max = -1;
	int index;
	index = 0;
	for (int i = 0; i < NUM; i++) {
		if (p[i].time > max) {
			max = p[i].time;
			index = i;
		}
	}

	return index;
}

int isHave(int fold, pageClass* p) {
	int i;
	for (int i = 0; i < NUM; i++) {
		if (fold == p[i].num) {
			return i;
		}
	}
	return -1;
}

void Lru(int fold, pageClass* p)
{
	int i;
	int val;
	val = isHave(fold, p);
	if (val >= 0)
	{
		p[val].time = 0;
		for (i = 0; i < NUM; i++)
			if (i != val)
				p[i].time++;
	}
	else
	{
		queue[++k] = fold;/*记录调入页面*/
		val = getLong(p);
		p[val].num = fold;
		p[val].time = 0;
		for (i = 0; i < NUM; i++)
			if (i != val)
				p[i].time++;
	}
}

int main() {
	int target[SUM];
	int i, j;
	srand((int)time(0));
	for (int i = 0; i < SUM; i++) {
		target[i] = random(PAGE_NUM);
	}//采用随机数来产生页面调用次序,假设页面在20里面
	init(pages, cash);
	for (int i = 0; i < SUM; i++) {
		Lru(target[i], pages);
		cash[0][i] = target[i];
		for (int j = 0; j < NUM; j++) {
			cash[j][i] = pages[j].num;
		}
	}

	cout << "the order of pages is:" << endl;
	for (int i = 0; i < SUM; i++) {
		cout << setw(3) << target[i];
	}
	cout << endl;
	cout << "cash changes:" << endl;
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < SUM; j++) {
			if (cash[i][j] == -1) {
				cout << setw(3) << " ";
			}
			else {
				cout << setw(3) << cash[i][j];
			}
		}
		cout << endl;
	}
	cout << "hit rate is " << endl;
	float hit_rate = 1 - (float)(k + 1) / SUM;
	cout << hit_rate << endl;
	cout << "Assume the time of cash reading is t and time of memory reading is 5t" << endl;
	cout << "the average reading time is" << endl;
	cout << hit_rate << "*t+" << 1 - hit_rate << "*5t" << endl;
	system("pause");
	return 0;
}