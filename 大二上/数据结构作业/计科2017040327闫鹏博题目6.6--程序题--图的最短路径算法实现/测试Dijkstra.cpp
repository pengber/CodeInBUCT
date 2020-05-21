#include "AdjMatrixDirNet.h"
using namespace std;

int main() {
	AdjMatrixDirNet<int, int> net;
	int num, vertex, elems[1000];
	int path[1000], temp;
	cin >> num;
	cin >> vertex;
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

	net.shortestPathDij(vertex, path);
	for (int i = 0; i < num; i++) {
		if (i == vertex);
		else {
			if (path[i] == 10000) {
				cout << -1 << " ";
			}
			else {
				cout << path[i] << " ";
			}
		}
	}
	system("pause");
	return 0;
}