#include <iostream>
using namespace std;

#define INFINITY 10
#define ARRAY 100
class AdjMatrixDirNet {
protected:
	int ** m_matrix;
	int * m_elems;
	int m_vertexSize;
public:
	AdjMatrixDirNet(int vexNum, int * elems);
	void insertEdge(int vex1, int vex2, int weight);
	void ford(int pathNet[][ARRAY], int pathInfo[][ARRAY]);

};
AdjMatrixDirNet::AdjMatrixDirNet(int vexNum, int * elems) {
	m_vertexSize = vexNum;
	m_elems = new int[m_vertexSize];
	m_matrix = (int**) new int *[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_elems[i] = elems[i];
		m_matrix[i] = new int[m_vertexSize];
		for (int j = 0; j < m_vertexSize; j++) {
			m_matrix[i][j] = INFINITY;
		}
	}
}
void AdjMatrixDirNet::insertEdge(int vex1, int vex2, int weight) {
	m_matrix[vex1][vex2] = weight;
}
void AdjMatrixDirNet::ford(int pathNet[][ARRAY], int pathInfo[][ARRAY]) {
	for (int i = 0; i < m_vertexSize; i++) {
		for (int j = 0; j < m_vertexSize; j++) {
			pathNet[i][j] = m_matrix[i][j];
			pathInfo[i][j] = j;
		}
	}
	/*cout << "**************测试pathNet******************" << endl;
	for (int i = 0; i < m_vertexSize; i++) {
		for (int j = 0; j < m_vertexSize; j++) {
			cout << pathNet[i][j] << " ";
		}
		cout << endl;
	}
	*/

	for (int i = 0; i < m_vertexSize; i++) {
		for (int j = 0; j < m_vertexSize; j++) {
			for (int k = 0; k < m_vertexSize; k++) {
				if (pathNet[j][k] >(pathNet[j][i] + pathNet[i][k])) {
					pathNet[j][k] = pathNet[j][i] + pathNet[i][k];
					pathInfo[j][k] = pathInfo[j][i];
				}

			}
		}
	}
}

int main() {
	int num, elems[1000];
	int  temp;
	int pathNet[100][100] = { 0 };
	int pathInfo[100][100] = { 0 };
	cin >> num;
	for (int i = 0; i < num; i++) {
		elems[i] = i;
	}
	AdjMatrixDirNet net(num, elems);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cin >> temp;
			if (temp != 0)
				net.insertEdge(i, j, temp);
		}
	}

	net.ford(pathNet, pathInfo);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (i == j) {
				cout << 0 << " ";			//这一行解决的是2到2本来就是INFINITY,但是如果2-1有边的话,2-1,1-2会出现小于INFINITY的现象
			}
			else {
				cout << pathNet[i][j] << " ";
			}
		}
		cout << endl;
	}
}