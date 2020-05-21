#include "AdjMatrixUndirGraph.h"

using namespace std;

void write(int &);

int main() {
	AdjMatrixUndirGraph<int> graph;
	BinaryTree<int> * forest = new BinaryTree<int>;
	int length, temp;
	int vertex[1000];
	cin >> length;
	for (int i = 0; i < length; i++) {
		vertex[i] = i;
	}
	graph.setGraph(vertex, length);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cin >> temp;
			if (temp != 0) {
				graph.insertEdge(i, j);
			}
		}
	}

	graph.DFSForest(forest);
	forest->preOrder(write);

	system("pause");
	return 0;
}

void write(int & elem) {
	cout << elem;
}