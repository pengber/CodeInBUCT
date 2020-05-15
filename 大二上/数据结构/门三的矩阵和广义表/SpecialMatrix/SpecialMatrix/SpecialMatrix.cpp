#include "SpecialMatrix.h"
#include <iostream>
using namespace std;

int main() {
	int n;
	
	cout << "ÇëÊäÈëÈý¶Ô½Ç¾ØÕó½×Êý:" << endl;
	cin >> n;
	cout << "ÇëÊäÈëÈý¶Ô½Ç¾ØÕó:" << endl;
	TriMatrix<int> matrixOne(n);
	matrixOne.display();

	system("pause");
	return 0;
}
