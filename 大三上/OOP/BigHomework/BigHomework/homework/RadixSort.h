#ifndef RADIXSORT_H_INCLUDE
#define RADIXSORT_H_INCLUDE
#include "SimpleLinkList.h"
#include <math.h>

//函数功能: 分发
//注意事项: 无
template <class ElemType>
void distribute(ElemType * elems, int n, int r, int d, int i, SimpleLinkList<ElemType> list[]) {
	int j, power;
	for (power = (int)pow((double)r, i - 1), j = 0; j < n; j++) {
		int index = (elems[j] / power) % r;
		list[index].insert(list[index].getLength() + 1, elems[j]);
	}
}
//函数功能: 收集

template <class ElemType>
void collect(ElemType * elems, int n, int r, int d, int i, SimpleLinkList<ElemType> * list) {
	for (int i = 0, k = 0; i < r; i++) {
		while (!list[i].isEmpty()) {
			ElemType tempElem;
			list[i].deleteElem(1, tempElem);
			elems[k++] = tempElem;
		}
	}
}
//函数功能: 实现基数排序
//注意事项: 1.数组下标0-n-1;r为基数,如果排列数字为10,d为关键字,数中最大数的位数
template <class ElemType>
void radixSort(ElemType * elems, int n, int r, int d) {
	//r为基数,d为关键字位数
	SimpleLinkList<ElemType> * list = new SimpleLinkList<ElemType>[r];

	for (int i = 1; i <= d; i++) {
		distribute(elems, n, r, d, i, list);
		collect(elems, n, r, d, i, list);
	}
}
#endif // !RADIXSORT_H_INCLUDE
