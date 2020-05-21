#include "TridiagonalMatix.h"
#include <iostream>
using namespace std;

int main() {
	TridiagonalMatrix<int> matrixA(3);
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			matrixA.setElem(i, j, i);
		}
	}
	matrixA.display();
	return 0;
}