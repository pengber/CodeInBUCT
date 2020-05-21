#include "HuffmanTree.h"
using namespace std;

int main() {
	char ch[100];
	int weight[100];
	int num;
	cout << "你可以建立一个哈夫曼树:" << endl;
	cout << "请输入字符总数:" << endl;
	cin >> num;
	cout << "请输入字符:" << endl;
	for (int i = 0; i < num; i++) {
		cin >> ch[i];
	}
	cout << "请输入他们的权重: " << endl;
	for (int i = 0; i < num; i++) {
		cin >> weight[i];
	}
	cout << "他们的编码依次是: " << endl;
		HuffmanTree<char, int> huffmanTree;
		huffmanTree.createHuffmanTree(ch, weight, 12);
	
	return 0;
}