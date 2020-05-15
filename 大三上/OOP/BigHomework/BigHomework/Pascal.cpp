/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/10/30
************************************************************************************/
/************************************************************************************
*Problem	:
			1.本程序在杨辉三角层数小于等于5的时候有良好的形状,但当n>5时,就会出现多位数,
			而多位数的位数和层数没有线性关系,如果改进程序的话,需要在求新的一行的数据入队
			的时候,计算新的一行中最大数的位数,此位数即为现在程序中所有有空格的地方的空格
			的位数。一种取巧的办法是设置每个输出为n位，这样在每行最大数为n位的话有着很漂亮
			的输出格式。
			2.不需要良好的形状时只需将现有程序" "的地方改为""，并且在cout << tempElemA语
			句后再 << " "即可。
*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:

************************************************************************************/


#include "SqQueue.h"
#include <iostream>
#include <iomanip>
using namespace std;

void priSpace(int n) {
	for (int i = 0; i < n; i++) {
		cout << setw(3) << " ";
	}
}
int main() {
	SqQueue<int> queueA(100);
	int level;
	int tempElemA, tempElemB;
	cout << "请输入杨辉三角的层数（推荐输入范围1-16，杨辉三角会很漂亮）：" << endl;
	cin >> level;
	
	for (int i = 1; i <= level+1; i++) {
		queueA.inQueue(0);
		if (i == 1) {
			queueA.inQueue(1);
			queueA.inQueue(0);
			
		}
		else {
			priSpace(level + 1 - i);
			for (int j = 1; j <= (2 * i + 1); j++) {
				if (j % 2 == 1) {
					queueA.outQueue(tempElemA);
					if (tempElemA != 0) cout << setw(3)<< tempElemA ;
					else cout << setw(3) << " ";
					queueA.getFrontElem(tempElemB);
					queueA.inQueue(tempElemA + tempElemB);
				}
				else {
					cout << setw(3) << " ";
				}
				
			}
			priSpace(level + 1 - i);
			cout << endl;
		}

		
	}
	return 0;
}