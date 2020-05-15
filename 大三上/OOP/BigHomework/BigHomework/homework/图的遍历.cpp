#include "AdjMatrixUndirGraph.h"
using namespace std;


void write(int &);
using namespace std;
int main() {
	AdjMatrixUndirGraph<int> graph;
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

	graph.DFSTraverse(0, write);
	cout << endl;

}

void write(int & elem) {
	cout << elem << " ";
}