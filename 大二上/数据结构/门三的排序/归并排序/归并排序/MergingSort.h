#ifndef MERGINGSORT_H_INCLUDE
#define MERGINGSORT_H_INCLUDE

/*Time:		2018/12/23
 *Tips:		1.归并程序的merge有问题,如果形参为同一个地址的话需要对merge进行改进。
			在这里我将形参的地址用了两个地址，但是里面内容一样来对严老师树上代码进行修正

 */
/**********************************mergingSort-Start*******************************/
//函数名称: merge(ElemType * startElems, ElemType * endElems, int s, int m, int t)
//函数功能: 实现startElems数组的归并排序,并将结果存储到endElems中
//注意事项: 如果startElems与endElems用的同一个数组地址,将会出现错误
template <class ElemType>
void merge(ElemType * startElems, ElemType * endElems, int s, int m, int t) {
	int  j, k;
	for (j = m + 1, k = s; s <= m && j <= t; k++) {
		if (startElems[s] < startElems[j]) endElems[k] = startElems[s++];
		else endElems[k] = startElems[j++];
	}

	while (s <= m) {
		endElems[k++] = startElems[s++];
	}
	while (j <= t) {
		endElems[k++] = startElems[j++];
	}
}
//函数名称: mergingSortHelp(ElemType * startElems, ElemType * endElems, int s, int t)
//函数功能: 实现归并排序
//注意事项: 因为merge函数的参数的地址不能为同一个地址,所以在使用merge函数传参时需要一个tempElems
//			数组存储将两个子列排序完后的序列以便整合成一个endElems;
template <class ElemType>
void mergingSortHelp(ElemType * startElems, ElemType * endElems, int s, int t) {
	if (s == t) endElems[t] = startElems[t];
	else {
		int m = (s + t) / 2;
		mergingSortHelp(startElems, endElems, s, m);
		mergingSortHelp(startElems, endElems, m + 1, t);
		ElemType * tempElems = new ElemType[t];
		for (int i = 1; i <= t; i++) {				//这复杂度就上来了.....
			tempElems[i] = endElems[i];			
		}

		merge(tempElems, endElems, s, m, t);
	}
}
//函数名称: mergingSort(ElemType * elems, int n)
//函数功能: 实现归并排序
template <class ElemType>
void mergingSort(ElemType * elems, int n) {
	mergingSortHelp(elems, elems, 1, n);
}
/*=================================mergingSort-End=================================*/
#endif // !MERGINGSORT
