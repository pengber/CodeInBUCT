//#include "MyString.h"						以后用自己的串来实现读取
#include <iostream>
#include <string>
using namespace std;
//函数名称: computeNext(char * p, int * next)
//函数功能: 实现KMP算法中next数组的求解
/*
 *注意事项:
 *1.p下标i:		0  1 2 3 4 5 6 7 8
 *其字串为:		A  B C A B C A A A
 *next[i] = j	-1 0 0 0 1 2 3 4 
 *next[i]存储的是i之前的字符串包含第i-1个字符的真子串的长度,比如next[7](4)表示p[0]-p[6]字
 *符串中包含p[6](A)的真字串的长度,同时,这个next[i(7)](4)值也是下次比较p[i(7)+1](A)应该与哪个值
 *再比较来得出包含p[7](A)的真子串长度,也就是p[8](A)应该与p[next[4]](B)比较,如果相等,那就是前一个
 *next值(4)加1。但是这里不相等，不相等则应该比较p[8](A)与p[next[1]](B),因为，这个next[i]值存储
 *的是p[i]之前的都已经匹配好的，下一次应该比较的i;也就是一直降低要求。（说不清楚😭）
 *
 *2.这也就是为什么初始化next[0] = -1的原因，因为其next[i]的意义是真字串长度和下一次应该比较的i的值
 *所以p[0]应该和p[-1]比较，所以其为-1；
 *注：A与B比较，A为被比较数，B为比较数。
 *3.当j < 0时，表明应该下回应该从比较数0比较，所以j++;而且这个j是已经比较好的值，所以被比较数也应该
 *加1来进行赋值next[i] = j且成为下次被比较数的i；而相等时，真子串长度加1，即j++;被比较数加一（成为下次
 *被比较数）且进行赋值;所以可以统一写为next[++i] = ++j;
 *
 *4.不相等时应该降低要求，也就是从当前比较数的next[i]值的p[next[i]]比较，被比较数不变，而下次比较数的下标
 *为当前比较数的next[i]；
*/

void computeNext(char * p, int * next) {
	int i = 0;		
	int j = -1;
	next[0] = -1;

	while (p[i] != '\0') {
		if (j < 0 || p[i] == p[j]) {
				i++;
				j++;
				next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

void KMP(char * s, char * p, int * next) {
	int i = 0;
	int j = 0;
	
	int sLength = strlen(s);
	int pLength = strlen(p);
	while (i < sLength && j < pLength) {
		if (j < 0 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];					//这句是精髓，也就是当不匹配时，j置为下次
											//要比较的字符在字串中的位置，i不动，因为下次
											//就该比较刚才失配位置的字符和新的p[j]
		}

		if (j == pLength) {
			cout << "字串在主串中位置为" << i - j << endl;
			j = next[j];
		}
	}
}

int main() {
	char s[1000], p[1000];
	int next[1000];

	cout << "请输入主串" << endl;
	gets_s(s);

	cout << "请输入字串:" << endl;
	gets_s(p);

	computeNext(p, next);
	KMP(s, p, next);
	return 0;
}