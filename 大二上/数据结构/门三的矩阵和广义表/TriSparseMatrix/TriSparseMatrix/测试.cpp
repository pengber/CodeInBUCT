#include "TriSparseMatrix.h"
#include <iostream>
using namespace std;

int main() {
	int rowOne, colOne;
	int rowTwo, colTwo;
	int i, j;
	int tempElem;
	cin >> rowOne >> colOne;
	TriSparseMatrix<int> matrix(rowOne, colOne, rowOne*colOne);
	for (i = 1; i <= rowOne; i++) {
		for (j = 1; j <= colOne; j++) {
			cin >> tempElem;
			if (tempElem != 0) {
				matrix.setElem(i, j, tempElem);
			}
		}
	}
	
	cin >> rowTwo >> colTwo;
	TriSparseMatrix<int> matrixTwo(rowTwo, colTwo, rowTwo*colTwo);
	for (i = 1; i <= rowTwo; i++) {
		for (j = 1; j <= colTwo; j++) {
			cin >> tempElem;
			if (tempElem != 0) {
				matrixTwo.setElem(i, j, tempElem);
			}
		}
	}

	matrix.mutiple(matrixTwo);
	TriSparseMatrix<int> matrixThree(rowOne, colTwo, rowOne * colTwo);

	system("pause");
	return 0;
}