#include "HuffmanTree.h"
using namespace std;

int main() {
	char ch[100] = { 'a' };
	int weight[100];
	int num;
	cin >> num;
	
	for (int i = 0; i < num; i++) {
		cin >> weight[i];
	}
	HuffmanTree<char, int> huffmanTree;
	huffmanTree.createHuffmanTree(ch, weight, num);
	
	return 0;
}