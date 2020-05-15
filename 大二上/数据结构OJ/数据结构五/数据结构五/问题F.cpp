#include <iostream>
#include <cstring>
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
void KMP(char * s, char * p, int * next) {
	int i = 0; 
	int j = 0;
	int sLength = strlen(s);				//the head file of "strlen" in oj si cstring;
	int pLength = strlen(p);

	while (i < sLength && j < pLength) {
		if (s[i] == p[j]|| j < 0) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}

		if (j == pLength) {
			cout << i - j + 1 << endl;
			j = next[j];
			return;
		}
	}
	cout << 0 << endl;
}
int main() {
	char p[1000];
	char s[1000];
	int next[1000];
	while (cin >> s) {
		cin >> p;
		computeNext(p, next);
		KMP(s, p, next);
	}
	
	
	return 0;
}