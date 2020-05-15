#include "AdjMatrixDirGraph.h"
#include <iostream>
using namespace std;

char preOrder[1000] = { '\0' };
char postOrder[1000] = { '\0' };
void write(char &);
int main() {
	AdjMatrixDirGraph<int> graph;
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
				graph.insertEdge(j, i);
			}
		}
	}
	
	graph.FindArticul();
	return 0;
}

void write(char & elem) {
	int i = 0;
	for (i; preOrder[i] != '\0'; i++) {
	}
	preOrder[i] = elem;
}

