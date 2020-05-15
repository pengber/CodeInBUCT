#include <bits/stdc++.h>
using namespace std;

struct rec {
	int a;
	int b;
	int c;

	bool flag = false;
};
void radixSort(rec * recs, int m);
void distribut(rec * , int , int , queue<rec> * );
void collec(rec * , int , int, queue<rec> *);

int main() {

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		int a, b, c;
		cin >> m;
		rec * rectangles = new rec[m];
		for (int j = 0; j < m; j++) {
			cin >> a >> b >> c;
			rectangles[j].a = a;
			if (b < c) {
				rectangles[j].b = c;
				rectangles[j].c = b;
				rectangles[j].flag = true;
			}
			else {
				rectangles[j].b = b;
				rectangles[j].c = c;
			}
		}
		for (int j = 0; j < m; j++) {
			cout << rectangles[j].a << rectangles[j].b << rectangles[j].c << endl;
		}
		radixSort(rectangles, m);
	}
	system("pause");
	return 0;
}

void radixSort(rec * recs,int m) {
	queue<rec> * que = new queue<rec>[m];
	for (int i = 0; i < 3; i++) {
		distribut(recs, i, m, que);
		collec(recs, i, m, que);
	}
}

void distribut(rec * recs, int i, int m, queue<rec> * que) {
	switch (i)
	{
	case 0:
		for (int j = 0; j < m; j++) {
			que[recs[j].a].push(recs[j]);
		}
		break;
	case 1:
		for (int j = 0; j < m; j++) {
			que[recs[j].b].push(recs[j]);
		}
		break;
	case 2:
		for (int j = 0; j < m; j++) {
			que[recs[j].c].push(recs[j]);
		}
		break;
	default:
		break;
	}
}

void collec(rec * recs, int i, int m, queue<rec> * que) {
	int k = 0;
	for (int j = 0; j < m; j++) {
		while (!que[j].empty()) {
			recs[k++] = que[j].front();
		}
	}	
}