#ifndef EXCHANGESORT_H_INCLUDE
#define EXCHANGESORT_H_INCLUDE

/**********************************bubbleSort**************************************/
//函数名称: void bubbleSort(ElemType * elems, int n)
//函数功能: 交换排序
//注意事项: 数组下标1-n;总数为n;
template <class ElemType>
void bSort(ElemType * elems, int n) {
	int i, j;

	for (i = 1; i < n; i++) {
		for (j = n - i; j > 0; j--) {
			if (elems[j] > elems[j + 1]) {
				elems[0] = elems[j];
				elems[j] = elems[j + 1];
				elems[j + 1] = elems[0];
			}
		}
	}
}
/*===============================bubbleSort-End====================================*/
/********************************quickSort-Start************************************/
template <class ElemType>
int partition(ElemType * elems, int low, int high) {
	elems[0] = elems[low];
	while (low < high) {
		while (low < high && elems[high] >= elems[0]) high--;
		elems[low] = elems[high];
		while (low < high && elems[low] <= elems[0]) low++;
		elems[high] = elems[low];
	}
	elems[low] = elems[0];
	return low;
}
//函数名称: quickSort(ElemType * elems, int high, int low = 1)
//函数功能: 实现数组下标high - low的快速排序,数组下标1-n存储n个需要排序的数
//注意事项: 为了保持接口的一致性,所以将low 放在参数最后以便带一个初始默认值1,
//			如果low传入参数,表明排序elems[low] - elems[high]的序列
template <class ElemType>
void quickSort(ElemType * elems,int high, int low = 1) {
	if (low < high) {
		int pivotKey = partition(elems, low, high); //这里是low - high
		quickSort(elems, pivotKey - 1, low);		//这里是high - low;
		quickSort(elems, high, pivotKey + 1);
	}
}
/*==============================quickSort-End========================================*/
#endif // !EXCHANGESORT_H_INCLUDE
