#include <iostream>

using namespace std;
#define CLIP_RANGE(value, min, max)  ( (value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)) )
//这个三目运算符的右操作数还是一个三目运算符表达式
int main() {
	/*int a, b, c;
	cin >> a >> b >> c;
	cout << CLIP_RANGE(a, b, c) << endl;
	*/
	float d;
	while (1) {
		cin >> d;
		double k = tan((45 + 44 * d) / 180 * 3.14159265857);
		cout << k << endl;
	}
	system("pause");
}