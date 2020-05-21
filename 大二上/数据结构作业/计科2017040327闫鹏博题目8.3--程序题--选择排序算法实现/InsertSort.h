#ifndef INSERTSORT_H_INCLUDE
#define INSERTSORT_H_INCLUDE

/***********************************直接插入排序***********************************/
//函数名称: void straightInsertSort(ElemType * elems, int n)
//函数功能: 对数组elems[1-n]进行排序
//注意事项: 数组下标1-n为n个需要排序的数
template <class ElemType>
void straightInsertSort(ElemType * elems, int n) {
	int i, j;
	for (i = 2; i <= n; i++) {
		if (elems[i] < elems[i - 1]) {
			elems[0] = elems[i];

			for (j = i - 1; j > 0 && elems[j] > elems[0]; j--) {
				elems[j + 1] = elems[j];
			}
			elems[j + 1] = elems[0];
		}
	}
}
/*===============================直接插入排序实现结束==============================*/

/********************************折半插入排序***************************************/
//函数名称: binaryInserSort(ElemType * elems, int n)
//函数功能: 实现折半排序
//注意事项: 数组下标1-n为n个需要排序的数
template <class ElemType>
void binaryInsertSort(ElemType * elems, int n) {
	int i, j, k;
	int low, high;
	for (i = 2; i <= n; i++) {
		elems[0] = elems[i];				//elems[0]为暂存单元
		low = 1; high = i - 1;
		while (low <= high) {				//利用折半法应当插入的的位置
			k = (low + high) / 2;
			if (elems[k] > elems[0]) high = k - 1;
			else low = k + 1;
		}
		//结束后low = high + 1既是应该插入的位置
		for (j = i - 1; j >= high + 1; --j) {//移动位置
			elems[j + 1] = elems[j];
		}
		elems[high + 1] = elems[0];
	}
}
/*=============================折半插入排序结束===================================*/


/********************************希尔排序****************************************/
template <class ElemType>
void shellInsert(ElemType * elems, int dk, int n) {
	int i, j;
	for (i = dk + 1; i <= n; i++) {
		if (elems[i] < elems[i - dk]) {
			elems[0] = elems[i];
			for (j = i - dk; j > 0 && elems[j] > elems[0]; j -= dk) {
				elems[j + dk] = elems[j];
			}
			elems[j + dk] = elems[0];
		}
	}
}
//函数名称: shellSortHelp(ElemType * elems, int * dlta, int t, int n)
//函数功能: 实现希尔排序
//注意事项: 数组下标1-n为待排序数,dlta数组为增量序列,t为增量的个数,n为待排序数数目
template <class ElemType>
void shellSortHelp(ElemType * elems, int * dlta, int t, int n) {
	for (int i = 1; i <= t; i++) {
		shellInsert(elems, dlta[i], n);
	}
}

template <class ElemType>
void shellSort(ElemType * elems, int n) {
	int dlta[20]; //最多排序数为2的20次方;dlta[0]存放n;
	int t = 0;
	dlta[0] = n;
	int i = 0;
	do {
		dlta[i + 1] = (dlta[i] + 1) / 2;
		t++;
		i++;
	} while (dlta[i] >= 2);

	shellSortHelp(elems, dlta, t, n);
}
/*================================希尔排序结实现结束=============================*/
#endif // !INSERTSORT_H_INCLUDE
