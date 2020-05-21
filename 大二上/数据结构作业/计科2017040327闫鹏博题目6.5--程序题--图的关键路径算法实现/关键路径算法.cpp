#include <bits/stdc++.h>
#include "AdjMatrixDirNet.h"
using namespace std;

int main() {
	AdjMatrixDirNet<int, int> net;
	int vexNum, tempVex;
	int elems[1000];
	cin >> vexNum;
	for (int i = 0; i < vexNum; i++) {
		elems[i] = i;
	}
	net.setGraph(elems, vexNum);
	for (int i = 0; i < vexNum; i++) {
		for (int j = 0; j < vexNum; j++) {
			cin >> tempVex;
			if (i != j && tempVex) {
				net.insertEdge(i, j, tempVex);
			}
		}
	}

	net.display();
	net.criticalPath();
	system("pause");
	return 0;
}