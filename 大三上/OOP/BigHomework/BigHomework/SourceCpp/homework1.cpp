#include "HuffmanTree.h"
#include <string>
using namespace std;

int main() {
	string code[9] = { "ADD","SUB","JMP","JOM","STO","SHR","CIL","CLA","STP" };
	float weight[9] = { 0.43, 0.13, 0.07, 0.06, 0.05, 0.01, 0.02, 0.22, 0.01 };
	//以第一次纸面作业的编码题作为元数据，因为重在考查系统结构，所以对信息的输入直接定义。
	HuffmanTree<string,float> tree(code,weight,9); 
	//改造了哈夫曼树的构造函数，在其构造函数中计算了平均码长，信息熵，信息冗余量

	system("pause");
	return 0;

}