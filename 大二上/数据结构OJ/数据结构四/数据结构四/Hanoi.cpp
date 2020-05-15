#include <iostream>
#include <cstdio>
using namespace std;
int order = 1;
void Hanoi(int n, char A, char B, char C) {
	if (n == 1) {
		printf("%2d. Move disk %d from %c to %c\n", order, n, A, C);
		order++;
	}
	else {
		Hanoi(n - 1, A, C, B);
		printf("%2d. Move disk %d from %c to %c\n", order, n, A, C);
		order++;
		Hanoi(n - 1, B, A, C);
	}
}
int main() {
	int m;
	while (cin >> m) {
		Hanoi(m, 'X', 'Y', 'Z');
		cout << endl;
		order = 1;
	}
	return 0;
}