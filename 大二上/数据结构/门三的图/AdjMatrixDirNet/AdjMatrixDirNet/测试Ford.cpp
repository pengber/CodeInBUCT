#include "AdjMatrixDirNet.h"
#include <iostream>
using namespace std;

int main() {
	
	AdjMatrixDirNet<int, int> net;
	int num, elems[1000];
	int  temp;
	int pathNet[100][100] = { 0 };
	int pathInfo[100][100] = { 0 };
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

	net.shortestPathFord(pathNet, pathInfo);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << pathNet[i][j] << " ";		
		}
		cout << endl;
	}
	return 0;
}