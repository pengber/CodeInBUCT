#include <string>
#include <iostream>
using namespace std;

int getLocation(string s1, string s2) {
	int i = 0;
	int j = 0;
	while (i < s1.size() && j < s2.size()) {
		if (s1[i] == s2[j]) {
			cout << s1[i];
			i++;
			j++;
		}
		else {
			cout << s1[i];
			i = i - j + 1;
			j = 0;
		}

		if (j== s2.size()) {
			
			return i - j + 1;
		}
	}
	return 0;
}

int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		int location = getLocation(s1, s2);
		cout << endl;
		cout << location << endl;
	}
	return 0;
}