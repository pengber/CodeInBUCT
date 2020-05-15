#include <bits/stdc++.h>
#include "AdjMatrixUndirNet.h"
using namespace std;

int main() {
	AdjMatrixUndirNet<int, int> net;
	int vertexSize;
	int vertex[1000];
	int weight;

	cin >> vertexSize;
	for (int i = 0; i < vertexSize; i++) {
		vertex[i] = i;
	}
	net.setGraph(vertex, vertexSize);

	for (int i = 0; i < vertexSize; i++) {
		for (int j = 0; j < vertexSize; j++) {
			cin >> weight;
			if (weight > 0) {
				net.insertEdge(i, j, weight);
			}
		}
	}

	net.kruskal();

	system("pause");
	return 0;
}