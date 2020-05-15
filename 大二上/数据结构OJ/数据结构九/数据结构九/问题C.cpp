#ifndef SELECTSORT_H_INCLUDE
#define SELECTSORT_H_INCLUDE

/********************************directSelectSort-Start**********************************/
template <class ElemType>
void directSelectSort(ElemType * elems, int n) {
	int i, j, k;

	for (i = 1; i <= n; i++) {
		elems[0] = elems[i];				//elems[0]存放最小元素比较值
		k = i;								//k存放最小元素数组下标
		for (j = i; j <= n; j++) {
			if (elems[j] < elems[0]) {		//如果从大到小排将此处<改为>即可
				k = j;
				elems[0] = elems[j];
			}
		}

		if (i != k) {
			elems[0] = elems[i];
			elems[i] = elems[k];
			elems[k] = elems[0];
		}
	}
}
/*===============================directSelectSort-End=================================*/


/*************************************heapSort-Start**********************************/
template <class ElemType>
void heapJust(ElemType * elems, int s, int m) {
	//已知elems[s-m]中除过elems[s]全都否和顶堆定义,本次将调整elems[s-m]为大顶堆
	ElemType recoder = elems[s];

	for (int j = s * 2; j <= m; j *= 2) {
		if (j < m && elems[j] < elems[j + 1]) ++j;
		if (!(recoder < elems[j])) break;	//注意!后面的表达式需要用括号括起来
		elems[s] = elems[j]; s = j;			//这里的思想和快速排序有些类似,不是比较一次交换一次
											//而是比较完了之后记录位置,再将值赋给对应位置
	}
	elems[s] = recoder;
}

template <class ElemType>
void heapSort(ElemType * elems, int n) {
	for (int i = n / 2; i > 0; i--) {
		heapJust(elems, i, n);
	}

	for (int i = n; i > 1; i--) {
		elems[0] = elems[1];				//交换
		elems[1] = elems[i];
		elems[i] = elems[0];

		heapJust(elems, 1, i - 1);			//交换之后再调整为大顶堆
	}
}
#endif // !SELECTSORT_H_INCLUDE

#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	int a[100001];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);

	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}


	return 0;
}