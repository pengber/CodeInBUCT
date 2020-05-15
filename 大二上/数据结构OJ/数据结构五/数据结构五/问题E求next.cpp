#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
void computeNext(char * p, int * next) {
	int i = 0;
	int j = -1;
	next[0] = -1;

	while (p[i] != '\0') {
		if (j < 0 || p[i] == p[j]) {
			next[++i] = ++j;
		}
		else {
			j = next[j];
		}
	}
}
int main() {
	char p[1000];
	int next[1000];

	gets_s(p);								//this line should be "gets(p)" in buctCoder.com
	computeNext(p, next);
	for (int i = 0; p[i] != '\0'; i++) {
		cout << next[i] + 1 << " ";
	}
	getchar();
	return 0;
}