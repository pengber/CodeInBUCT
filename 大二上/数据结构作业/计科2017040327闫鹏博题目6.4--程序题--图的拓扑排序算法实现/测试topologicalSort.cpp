#include "AdjMatrixDirNet.h"
using namespace std;

int main() {
	AdjMatrixDirNet<int, int> net;
	int num, elems[1000];
	int  temp;
	cin >> num;
	for (int i = 0; i < num; i++) {
		elems[i] = i;
	}
	net.setGraph(elems, num);

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cin >> temp;
			if (temp != 0)
				net.insertEdge(i, j, temp);
		}
	}

	net.topologicalSort();
	return 0;
}